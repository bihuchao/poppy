// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_MATH_MATHUTIL_H
#define POPPY_MATH_MATHUTIL_H

#include <math.h>

namespace poppy
{

const float kPi = 3.14159265f;
const float k2Pi = kPi * 2.0f;
const float kPiOver2 = kPi / 2.0f;
const float k1OverPi = 1.0f / kPi;
const float k1Over2Pi = 1.0f / k2Pi;
const float kPiOver180 = kPi / 180.0f;
const float k180OverPi = 180.f / kPi;

inline float degToRad(float deg)
{
  return deg * kPiOver180;
}

inline float WrapPi(float theta)
{
  theta += kPi;
  theta -= floor(theta * k1Over2Pi) *k2Pi;
  theta -= kPi;

  return theta;
}

inline bool floatEqual(float v1, float v2)
{
  static const float kEpsilon = 0.00001;
  return fabs(v1 - v2) <= kEpsilon;
}

}

#endif
