// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_MATH_VECTOR3_H
#define POPPY_MATH_VECTOR3_H

#include <math.h>

namespace poppy
{

class Vector3
{
  public:
    Vector3(): x_(0.0f), y_(0.0f), z_(0.0f) {}
    Vector3(const Vector3 &a): x_(a.x_),
      y_(a.y_), z_(a.z_) {}
    Vector3(float x, float y, float z): x_(x), y_(y), z_(z) {}
    Vector3 &operator=(const Vector3 &a) {
      x_ = a.x_;
      y_ = a.y_;
      z_ = a.z_;

      return *this;
    }

    Vector3 &operator +=(const Vector3 &rhs) {
      x_ += rhs.x_; y_ += rhs.y_ ; z_ += rhs.z_;

      return *this;
    }

    Vector3 &operator *=(float a)
    {
      x_ *= a; y_ *= a; z_ *= a;
      return *this; 
    }

    Vector3 &operator /=(float a)
    {
      float oneOverA = 1.0f / a;
      x_ *= oneOverA; y_ *= oneOverA; z_ *= oneOverA;
      return *this; 
    }

    Vector3 operator -=(const Vector3& rhs) {
      x_ -= rhs.x_; y_ -= rhs.y_ ; z_ -= rhs.z_;

      return *this;
    }

    Vector3 operator -() const { Vector3(-x_, -y_, -z_); }

    Vector3 operator *(float a) const
    {
      return Vector3(a * x_, a * y_, a * z_); 
    }

    Vector3 operator /(float a) const
    {
      float oneOverA = 1.0f / a; 
      return Vector3(x_ * oneOverA, y_ * oneOverA, z_ * oneOverA);
    }

    void zero() { x_ = y_ = z_ = 0; }
    void normalize() {
      float magSq = x_ * x_ + y_ * y_ + z_ * z_; 
      if (magSq > 0.0f)
      {
        float oneOverMag = 1.0f / sqrt(magSq); 
        x_ *= oneOverMag;
        y_ *= oneOverMag;
        z_ *= oneOverMag;
      }
    }

    float mag()
    {
      return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
    }

    const static Vector3 kZeroVector3;

    float x_, y_, z_;
};

inline bool operator ==(const Vector3 &lhs, const Vector3 &rhs)
{
  return (lhs.x_ == rhs.x_) 
    && (lhs.y_ == rhs.y_)
    && (lhs.z_ == rhs.z_);
}

inline bool operator !=(const Vector3 &lhs, const Vector3 &rhs)
{
  return (lhs.x_ != rhs.x_) 
    || (lhs.y_ != rhs.y_)
    || (lhs.z_ != rhs.z_);
}

inline Vector3 operator +(const Vector3& lhs, const Vector3& rhs)
{
  Vector3(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_,
      lhs.z_ + rhs.z_);
}

inline Vector3 operator -(const Vector3& lhs, const Vector3& rhs)
{
  Vector3(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_,
      lhs.z_ - rhs.z_);
}

inline float operator *(const Vector3& lhs, const Vector3& rhs)
{
  return lhs.x_ * rhs.x_ + lhs.y_ * rhs.y_
    + lhs.z_ * rhs.z_;
}

inline Vector3 crossProduct(const Vector3& a, const Vector3& b)
{
  return Vector3(
      a.y_ * b.z_ - a.z_ * b.y_,
      a.z_ * b.x_ - a.x_ * b.z_,
      a.x_ * b.y_ - a.y_ * b.x_
      );
}

inline Vector3 operator *(float k, const Vector3& v)
{
  return Vector3(k * v.x_, k * v.y_, k * v.z_);
}

inline float distance(const Vector3& a, const Vector3& b)
{
  float dx = a.x_ - b.x_;
  float dy = a.y_ - b.y_;
  float dz = a.z_ - b.z_;

  return sqrt(dx * dx + dy * dy + dz * dz);
}

}
#endif

