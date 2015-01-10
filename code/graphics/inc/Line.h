/*
 * Linef.h
 *
 *  Created on: 2015Äê1ÔÂ7ÈÕ
 *      Author: Administrator
 */

#ifndef POPPY_MATH_LINE_H
#define POPPY_MATH_LINE_H

#include <stdint.h>
#include <VideoSystem.h>

namespace poppy
{

class Line
{
 public:
  Line(float x1, float y1, float x2, float y2);

  float getX(float y)
  {
    if (vLine_)
    {
      return x1_;
    }

    return (y - b_) / k_;
  }

  float getY(float x)
  {
    if (hLine_)
    {
      return y1_;
    }

    return k_ * x + b_;
  }
  bool vLine() { return vLine_; }
  bool hLine() { return hLine_; }
  operator bool() { return valid_; }

  int clip(int w, int h, int *x1, int *y1,
           int *x2, int *y2);

 private:
  float k_, b_;
  bool valid_;
  bool vLine_, hLine_;
  float x1_, y1_, x2_, y2_;

  static const float kEpsilon = 0.00001;

  static const uint32_t kClipCodeC = 0x00;
  static const uint32_t kClipCodeN = 0x08;
  static const uint32_t kClipCodeS = 0x04;
  static const uint32_t kClipCodeE = 0x02;
  static const uint32_t kClipCodeW = 0x01;

  uint32_t position(int w, int h, float x, float y)
  {
    uint32_t pos = 0u;
    if (x < 0)      { pos |= kClipCodeW; }
    if (x > w - 1)  { pos |= kClipCodeE; }
    if (y < 0)      { pos |= kClipCodeN; }
    if (y > h - 1)  { pos |= kClipCodeS; }

    return pos;
  }
};

}

#endif /* CODE_3DMATH_INC_LINEF_H_ */
