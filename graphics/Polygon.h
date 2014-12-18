// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_GRAPHICS_POLYGON_H
#define POPPY_GRAPHICS_POLYGON_H\


#include <vector>
#include <tr1/memory>

#include "Vector3.h"

namespace poppy
{

class Polygon
{
 public:
  enum TranType
  {

  };
 private:
  uint32_t state_;
  uint32_t attr_;
  uint32_t color_;

  std::tr1::shared_ptr<std::vector<Vector3> > vTotalList_;
  int vert[3];

  Vector3 vlist_[3];
  Vector3 tlist_[3];

  int polyType_;
};

}

#endif
