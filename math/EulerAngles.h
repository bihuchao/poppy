// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_MATH_EULERANGLES_H
#define POPPY_MATH_EULERANGLES_H

#include "Matrix.h"

namespace poppy
{

class EulerAngles
{
 public:
  EulerAngles()
   :heading(0.0f), pitch(0.0f), bank(0.0f) { }
  EulerAngles(float h, float p, float b)
      :heading(h), pitch(p), bank(b) { }

  void identity() { heading = pitch = bank = 0.0f; }
  void canonize();

  Matrix<4, 4> getObjectToWorldMatrix();
  Matrix<4, 4> getWorldToObjectMatrix();

  float heading, pitch, bank;
};

extern const EulerAngles kEulerAnglesIdentity;

}

#endif
