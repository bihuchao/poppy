// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include <stdlib.h>
#include <stdio.h>

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
  uint32_t pointPos1 = getPosition(w, h, *x1, *y1);
  uint32_t pointPos2 = getPosition(w, h, *x2, *y2);

  int tx1 = *x1, ty1 = *y1;
  int tx2 = *x2, ty2 = *y2;

  if (pointPos1 & pointPos2)
  {
    return 0;
  }

  if (pointPos1 == kClipCodeC && pointPos2 == kClipCodeC)
  {
    return 1;
  }

  while ((pointPos1 != kClipCodeC) || (pointPos2 != kClipCodeC))
  {
    uint32_t pos = 0u;
    Line2 line(tx1, ty1, tx2, ty2);
    int x = 0, y = 0;

    if (pointPos1 != 0)
    {
      pos = pointPos1;
    }
    else
    {
      pos = pointPos2;
    }

    if (pos & kClipCodeN)
    {
      y = 0;
      line.getX(y, &x);
    }
    else if (pos & kClipCodeS)
    {
      y = h - 1;
      line.getX(y, &x);
    }
    else if (pos & kClipCodeW)
    {
      x = 0;
      line.getY(x, &y);
    }
    else if (pos & kClipCodeE)
    {
      x = w - 1;
      line.getY(x, &y);
    }

    if (pos == pointPos1)
    {
      tx1 = x;
      ty1 = y;
      pointPos1 = getPosition(w, h, tx1, ty1);
    }
    else
    {
      tx2 = x;
      ty2 = y;
      pointPos2 = getPosition(w, h, tx2, ty2);
    }

    if (pointPos1 & pointPos2)
    {
      return 0;
    }
  }

  *x1 = tx1, *y1 = ty1;
  *x2 = tx2, *y2 = ty2;

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

  //Àƒ…·ŒÂ»Î
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
