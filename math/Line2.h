// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_MATH_LINE2_H
#define POPPY_MATH_LINE2_H

#include <stdint.h>

namespace poppy
{

class Line2
{
 public:
  Line2(int x1 = 0, int y1 = 0, int x2 = 1, int y2 = 1);

  int clip(int w, int h, int *x1, int *y1, int *x2, int *y2);
  int crossPoint(const Line2& line, int *px, int *py);
  int getY(int x, int *py);
  int getX(int y, int *px);
  bool vLine() { return vLine_; }
  bool hLine() { return hLine_; }


 private:
  float k_;
  float kb_;
  float a_;
  float b_;
  float c_;

  bool vLine_;
  bool hLine_;
  int x_;
  int y_;

  const static uint32_t kClipCodeC = 0x00;
  const static uint32_t kClipCodeN = 0x08;
  const static uint32_t kClipCodeS = 0x04;
  const static uint32_t kClipCodeE = 0x02;
  const static uint32_t kClipCodeW = 0x01;

  uint32_t getPosition(int w, int h, int x, int y);
};

}

#endif /* MATH_POINT2_H_ */
