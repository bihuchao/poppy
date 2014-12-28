// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include "Matrix.h"

namespace poppy
{

Vector3 operator*(const Vector3& lhs, const Matrix<3, 3>& rhs)
{
  Vector3 ret;

  ret.x = lhs.x * rhs.getItem(1, 1) + lhs.y * rhs.getItem(2, 1)
            + lhs.z * rhs.getItem(3, 1);
  ret.y = lhs.x * rhs.getItem(1, 2) + lhs.y * rhs.getItem(2, 2)
            + lhs.z * rhs.getItem(3, 2);
  ret.z = lhs.x * rhs.getItem(1, 3) + lhs.y * rhs.getItem(2, 3)
            + lhs.z * rhs.getItem(3, 3);

  return ret;
}

Vector3 operator*(const Vector3& lhs, const Matrix<4, 4>& rhs)
{
  Matrix<1, 4> tmpMatrix1, tmpMatrix2;

  tmpMatrix1.setItem(1, 1, lhs.x);
  tmpMatrix1.setItem(1, 2, lhs.y);
  tmpMatrix1.setItem(1, 3, lhs.z);
  tmpMatrix1.setItem(1, 4, 1.0f);

  tmpMatrix2 = tmpMatrix1 * rhs;

  return Vector3(tmpMatrix2.getItem(1, 1) / tmpMatrix2.getItem(1, 4),
                 tmpMatrix2.getItem(1, 2) / tmpMatrix2.getItem(1, 4),
                 tmpMatrix2.getItem(1, 3) / tmpMatrix2.getItem(1, 4));
}

}
