// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_GRAPHICS_OBJECT_H
#define POPPY_GRAPHICS_OBJECT_H

#include <stdint.h>
#include <string.h>

#include <vector>
//#include <tr1/memory>

#include "Vector3.h"
#include "EulerAngles.h"

namespace poppy
{

class Polygon
{
 public:
  Polygon() { memset(this, 0, sizeof(*this)); }

  Polygon(uint32_t attr, uint32_t color,
          std::vector<Vector3>* pvlist,
          int p1, int p2, int p3)
    : state_(0u), attr_(attr), color_(color),
      pvlist_(pvlist)
  { vert_[0] = p1, vert_[1] = p2, vert_[2] = p3; }

  uint32_t state_;
  uint32_t attr_;
  uint32_t color_;

  std::vector<Vector3>* pvlist_;
  int vert_[3];
};

class Object
{
 public:
  Object();
 private:
  uint32_t attr_;
  uint32_t state_;

  float avgRadius;
  float maxRadius;

  EulerAngles dir;
  Vector3 ux, vy, nz;

  Vector3 pos_;
  std::string name;
  uint32_t id;
  std::vector<Vector3> vlistLocal_;
  std::vector<Vector3> vlistTrans_;

  std::vector<Polygon> polyList_;
};

}

#endif
