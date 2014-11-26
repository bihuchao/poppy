// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_MATH_VECTOR3_H
#define POPPY_MATH_VECTOR3_H

namespace poppy
{

class Vector3
{
  public:
    Vector3(): x_(0.0f), y_(0.0f), z_(0.0f) {}
    Vector3(const Vector3 &a): x_(a.getx()),
      y_(a.gety()), z_(a.getz()) {}
    Vector3(float x, float y, float z): x_(x), y_(y), z_(z) {}
    Vector3 &operator=(const Vector3 &a) {
      x_ = a.getx();
      y_ = a.gety();
      z_ = a.getz();
    }
    float getx() const { return x_; }
    float gety() const { return y_; }
    float getz() const { return z_; }

    const static Vector3 kZeroVector3;
  private:
    float x_, y_, z_;
};

}
#endif

