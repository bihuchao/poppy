// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include "EulerAngles.h"
#include "MathUtil.h"

namespace poppy
{

const EulerAngles kEulerAnglesIdentity(0.0f, 0.0f, 0.0f);

void EulerAngles::canonize()
{
  pitch = WrapPi(pitch);

  if (pitch < -kPiOver2)
  {
    pitch = -kPi - pitch;
    heading += kPi;
    bank += kPi;
  }
  else
  {
    pitch = kPi - pitch;
    heading += kPi;
    bank += kPi;
  }

  if (fabs(pitch) > kPiOver2 - 1e-4)
  {
    heading += bank;
    bank = 0.0f;
  }
  else
  {
    bank = WrapPi(bank);
  }

  heading = WrapPi(heading);
}

Matrix<4, 4> EulerAngles::getObjectToWorldMatrix() const
{
  Matrix<4, 4> ret;
  ret.zero();

  float item = cos(heading) * cos(bank) + sin(heading) * sin(pitch) * sin(bank);
  ret.setItem(1, 1, item);

  item = sin(bank) * cos(pitch);
  ret.setItem(1, 2, item);

  item = -sin(heading) * cos(bank) + cos(heading) * sin(pitch) * sin(bank);
  ret.setItem(1, 3, item);

  item = -cos(heading) * sin(bank) + sin(heading) * sin(pitch) * cos(bank);
  ret.setItem(2, 1, item);

  item = cos(bank) * cos(pitch);
  ret.setItem(2, 2, item);

  item = sin(bank) * sin(heading) + cos(heading) * sin(pitch) * cos(bank);
  ret.setItem(2, 3, item);

  item = sin(heading) * cos(pitch);
  ret.setItem(3, 1, item);

  item = - sin(pitch);
  ret.setItem(3, 2, item);

  item = cos(heading) * cos(pitch);
  ret.setItem(3, 3, item);

  ret.setItem(4, 4, 1.0f);

  return ret;
}

Matrix<4, 4> EulerAngles::getWorldToObjectMatrix() const
{
  Matrix<4, 4> ret;
  ret.zero();

  float item = cos(heading) * cos(bank) + sin(heading) * sin(pitch) * sin(bank);
  ret.setItem(1, 1, item);

  item = - cos(heading) * sin(bank) + sin(heading) * sin(pitch) * cos(bank);
  ret.setItem(1, 2, item);

  item = sin(heading) * cos(pitch);
  ret.setItem(1, 3, item);

  item = sin(bank) * cos(pitch);
  ret.setItem(2, 1, item);

  item = cos(bank) * cos(pitch);
  ret.setItem(2, 2, item);

  item = -sin(pitch);
  ret.setItem(2, 3, item);

  item = -sin(heading) * cos(bank) + cos(heading) * sin(pitch) * sin(bank);
  ret.setItem(3, 1, item);

  item = sin(bank) * sin(heading) + cos(heading) * sin(pitch) * cos(bank);
  ret.setItem(3, 2, item);

  item = cos(heading) * cos(pitch);
  ret.setItem(3,3, item);

  ret.setItem(4, 4, 1.0f);

  return ret;
}

}
