// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_GRAPHICS_OBJECT_H
#define POPPY_GRAPHICS_OBJECT_H

#include <stdint.h>

#include <vector>
//#include <tr1/memory>

#include "Vector3.h"

namespace poppy
{

struct Polygon
{
  uint32_t state_;
  uint32_t attr_;
  uint32_t color_;

  std::vector<Vector3>* vlist;
  int vert[3];
};

}

#endif
