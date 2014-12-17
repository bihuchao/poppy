// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPyMATH_VECTOR3_H
#define POPPyMATH_VECTOR3_H

#include <math.h>

namespace poppy
{

class Vector3
{
 public:
  Vector3()
      : x(0.0f),
        y(0.0f),
        z(0.0f) { }
  Vector3(const Vector3 &a)
      : x(a.x),
        y(a.y),
        z(a.z) { }

  Vector3(float x, float y, float z)
      : x(x),
        y(y),
        z(z) { }

  Vector3 &operator=(const Vector3 &a)
  {
    x = a.x;
    y = a.y;
    z = a.z;

    return *this;
  }

  Vector3 &operator +=(const Vector3 &rhs)
  {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;

    return *this;
  }

  Vector3 &operator *=(float a)
  {
    x *= a;
    y *= a;
    z *= a;
    return *this;
  }

  Vector3 &operator /=(float a)
  {
    float oneOverA = 1.0f / a;
    x *= oneOverA;
    y *= oneOverA;
    z *= oneOverA;
    return *this;
  }

  Vector3 operator -=(const Vector3& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;

    return *this;
  }

  Vector3 operator -() const
  {
    return Vector3(-x, -y, -z);
  }

  Vector3 operator *(float a) const
  {
    return Vector3(a * x, a * y, a * z);
  }

  Vector3 operator /(float a) const
  {
    float oneOverA = 1.0f / a;
    return Vector3(x * oneOverA, y * oneOverA, z * oneOverA);
  }

  void zero()
  {
    x = y = z = 0;
  }
  void normalize()
  {
    float magSq = x * x + y * y + z * z;
    if (magSq > 0.0f) {
      float oneOverMag = 1.0f / sqrt(magSq);
      x *= oneOverMag;
      y *= oneOverMag;
      z *= oneOverMag;
    }
  }

  float mag()
  {
    return sqrt(x * x + y * y + z * z);
  }

  const static Vector3 kZeroVector3;

  float x, y, z;
};

inline bool operator ==(const Vector3 &lhs, const Vector3 &rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);
}

inline bool operator !=(const Vector3 &lhs, const Vector3 &rhs)
{
  return (lhs.x != rhs.x) || (lhs.y != rhs.y) || (lhs.z != rhs.z);
}

inline Vector3 operator +(const Vector3& lhs, const Vector3& rhs)
{
  return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

inline Vector3 operator -(const Vector3& lhs, const Vector3& rhs)
{
  return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

inline float operator *(const Vector3& lhs, const Vector3& rhs)
{
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

inline Vector3 crossProduct(const Vector3& a, const Vector3& b)
{
  return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
                 a.x * b.y - a.y * b.x);
}

inline Vector3 operator *(float k, const Vector3& v)
{
  return Vector3(k * v.x, k * v.y, k * v.z);
}

inline float distance(const Vector3& a, const Vector3& b)
{
  float dx = a.x - b.x;
  float dy = a.y - b.y;
  float dz = a.z - b.z;

  return sqrt(dx * dx + dy * dy + dz * dz);
}

}
#endif

