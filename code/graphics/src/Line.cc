/*
 * Linef.cc
 *
 *  Created on: 2015Äê1ÔÂ7ÈÕ
 *      Author: Administrator
 */

#include "../inc/Line.h"
#include <math.h>

#include "Logger.h"
#include "MathUtil.h"

namespace poppy
{

Line::Line(float x1, float y1, float x2, float y2)
  : k_(0.0f), b_(0.0f), valid_(true), vLine_(false),
    hLine_(false), x1_(0.0f), y1_(0.0f), x2_(0.0f),
    y2_(0.0f)
{
  if (floatEqual(x1, x2))
  {
    if (floatEqual(y1, y2))
    {
      valid_ = false;
      LOG_ERROR("point1 is equal to p2, %f %f %f %f\n",
                x1, y1, x2, y2);
      return;
    }

    vLine_ = true;
    x1_ = x1, y1_ = y1;
    x2_ = x2, y2_ = y2;
    return;
  }
  else if (floatEqual(y1, y2))
  {
    hLine_ = true;

    x1_ = x1, y1_ = y1;
    x2_ = x2, y2_ = y2;

    b_ = y1;
    return;
  }

  k_ = (y2 - y1) / (x2 - x1);
  b_ = y1 - k_ * x1;

  x1_ = x1, y1_ = y1;
  x2_ = x2, y2_ = y2;
}

int Line::clip(int w, int h, int *x1, int *y1,
               int *x2, int *y2)
{
  float cx1 = x1_;
  float cy1 = y1_;
  float cx2 = x2_;
  float cy2 = y2_;
  float x, y;
  *x1 = cx1 + 0.5, *y1 = cy1 + 0.5;
  *x2 = cx2 + 0.5, *y2 = cy2 + 0.5;

  if (!valid_)
  {
    LOG_ERROR("Line is invalid!!!\n");
    return 0;
  }

  uint32_t pos1 = position(w, h, cx1, cy1);
  uint32_t pos2 = position(w, h, cx2, cy2);

  if (pos1 & pos2)
  {
    return 0;
  }

  if ((pos1 == kClipCodeC) && (pos2 == kClipCodeC))
  {
    return 1;
  }

  while ((pos1 != kClipCodeC) || (pos2 != kClipCodeC))
  {
    uint32_t pos = 0u;
    pos = (pos1 != kClipCodeC) ? pos1 : pos2;

    if ((pos & kClipCodeN) || (pos & kClipCodeS))
    {
      y = (pos & kClipCodeN) ? 0 : (h - 1);
      x = getX(y);
    }
    else if ((pos & kClipCodeE) || (pos & kClipCodeW))
    {
      x = (pos & kClipCodeW) ? 0 : (w - 1);
      y = getY(x);
    }

    if (pos == pos1)
    {
      cx1 = x; cy1 = y;
      pos1 = position(w, h, cx1, cy1);
    }
    else
    {
      cx2 = x; cy2 = y;
      pos2 = position(w, h, cx2, cy2);
    }

    if (pos1 & pos2)
    {
      return 0;
    }
  }

  *x1 = cx1 + 0.5, *y1 = cy1 + 0.5;
  *x2 = cx2 + 0.5, *y2 = cy2 + 0.5;

  return 1;
}

}
