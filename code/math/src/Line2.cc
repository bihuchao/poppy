// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include <stdlib.h>

#include "Line2.h"
#include "Logger.h"

namespace poppy
{

Line2::Line2(int x1, int y1, int x2, int y2)
  :k_(0.0f), kb_(0.0f), a_(0.0f), b_(0.0f), c_(0.0f),
   vLine_(false), hLine_(false), x_(0), y_(0)
{
  if (x1 == x2 && y1 == y2)
  {
    LOG_ERROR("point1 is equal to point2, "
        "x1: %d, y1: %d, x2: %d, y2: %d\n", x1, y1, x2, y2);
    x1 = y1 = 0;
    x2 = y2 = 1;
  }
  else
  {
    a_ = y1 - y2;
    b_ = x2 - x1;
    c_ = x1 * y2 - x2 * y1;

    if (x1 == x2)
    {
      //VLine
      vLine_ = true;
      x_ = x1;
    }
    else if (y1 == y2)
    {
      //HLine
      k_ = 0.0f;
      kb_ = y1;
      hLine_ = true;
      y_ = y1;
    }
    else
    {
      k_ = (y2 - y1) / (float)(x2 - x1);
      kb_ = y1 - ((y2 - y1) / (float)(x2 - x1)) * x1;
    }
  }
}

int Line2::getY(int x, int *py)
{
  if (vLine_)
  {
    LOG_ERROR("Line is vLine!\n");
    return -1;
  }

  if (hLine_)
  {
    *py = y_;
    return 0;
  }

  *py = k_ * x + kb_ + 0.5;

  return 0;
}

int Line2::getX(int y, int *px)
{
  if (hLine_)
  {
    LOG_ERROR("Line is hLine!\n");
    return -1;
  }

  if (vLine_)
  {
    *px = x_;
    return 0;
  }

  *px = (y - kb_) / k_ + 0.5;
  return 0;
}

int Line2::clip(int w, int h, int *x1, int *y1, int *x2, int *y2)
{
  Line2 line(*x1, *y1, *x2, *y2);
  uint32_t pointPos1 = getPosition(w, h, *x1, *y1);
  uint32_t pointPos2 = getPosition(w, h, *x2, *y2);

  if (pointPos1 & pointPos2)
  {
    return 0;
  }

  if (pointPos1 == kClipCodeC && pointPos2 == kClipCodeC)
  {
    return 1;
  }

  if (line.vLine())
  {
    if (pointPos1 & kClipCodeN)
    {
      *y1 = 0;
    }
    else if (pointPos1 & kClipCodeS)
    {
      *y1 = h - 1;
    }

    if (pointPos2 & kClipCodeN)
    {
      *y2 = 0;
    }
    else if (pointPos2 & kClipCodeS)
    {
      *y2 = h - 1;
    }

    return 1;
  }

  if (line.hLine())
  {
    if (pointPos1 & kClipCodeE)
    {
      *x1 = w - 1;
    }
    else if (pointPos1 & kClipCodeW)
    {
      *x1 = 0;
    }

    if (pointPos2 & kClipCodeE)
    {
      *x2 = w - 1;
    }
    else if (pointPos2 & kClipCodeW)
    {
      *x2 = 0;
    }

    return 1;
  }

  //求和X轴的交点
  int crossNum = 0;
  int cx[2] = {0};
  int cy[2] = {0};

  cy[crossNum] = 0;
  line.getX(cy[crossNum], &cx[crossNum]);
  if (cx[crossNum] >= 0 && cx[crossNum] < w)
  {
    crossNum++;
  }

  //和Y轴的交点
  cx[crossNum] = 0;
  line.getY(cx[crossNum], &cy[crossNum]);
  if (cy[crossNum] >= 0 && cy[crossNum] < h - 1)
  {
    if (crossNum == 1 && (cx[0] != cx[1] || cy[0] != cy[1]))
    {
      crossNum++;
    }
  }

  //和X轴平行边的交点
  if (crossNum < 2)
  {
    cy[crossNum] = h -1;
    line.getX(cy[crossNum], &cx[crossNum]);
    if (cx[crossNum] >= 0 && cx[crossNum] < w)
    {
      if (crossNum == 1 && (cx[0] != cx[1] || cy[0] != cy[1]))
      {
        crossNum++;
      }
    }
  }

  //和y轴平行边的交点
  if (crossNum < 2)
  {
    cx[crossNum] = w -1;
    line.getY(cx[crossNum], &cy[crossNum]);
    if (cy[crossNum] >= 0 && cy[crossNum] < h)
    {
      if (crossNum == 1 && (cx[0] != cx[1] || cy[0] != cy[1]))
      {
        crossNum++;
      }
    }
  }

  if (crossNum < 2)
  {
    return 0;
  }

  if (pointPos1 != kClipCodeC)
  {
    if (abs(*x1 - cx[0]) < abs(*x1 - cx[1]))
    {
      *x1 = cx[0];
      *y1 = cy[0];
    }
    else
    {
      *x1 = cx[1];
      *y1 = cy[1];
    }
  }

  if (pointPos2 != kClipCodeC)
  {
    if (abs(*x2 - cx[0]) < abs(*x2 - cx[1]))
    {
      *x2 = cx[0];
      *y2 = cy[0];
    }
    else
    {
      *x2 = cx[1];
      *y2 = cy[1];
    }
  }
  return 1;
}

int Line2::crossPoint(const Line2& line, int *px, int *py)
{
  if (vLine_ && line.vLine_)
  {
    LOG_ERROR("Lines are both vLine\n");
    return -1;
  }

  if (!vLine_ && !line.vLine_)
  {
    if (k_ == line.k_)
    {
      LOG_ERROR("Lines are parallel!\n");
      return -1;
    }
  }

  float d = a_ * line.a_ - line.a_ * b_;

  //四舍五入
  *px = (b_ * line.c_ - line.b_ * c_) / d + 0.5f;
  *py = (c_ * line.a_ - line.c_ * a_) / d + 0.5f;

  return 0;
}

uint32_t Line2::getPosition(int w, int h, int x, int y)
{
  uint32_t position = 0u;
  int maxX = w - 1;
  int maxY = h - 1;

  if (y < 0)
  {
    position |= kClipCodeN;
  }

  if (y > maxY)
  {
    position |= kClipCodeS;
  }

  if (x < 0)
  {
    position |= kClipCodeW;
  }

  if (x > maxX)
  {
    position |= kClipCodeE;
  }

  return position;
}

}
