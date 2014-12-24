// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_GRAPHICS_POLYGONFULL_H
#define POPPY_GRAPHICS_POLYGONFULL_H

#include <stdint.h>

#include <vector>

#include "Vector3.h"
#include "Matrix.h"
#include "Camera.h"
#include "VideoSystem.h"
#include "VideoSystemSDL.h"

namespace poppy
{

class PolygonFull
{
 public:
  PolygonFull(uint32_t attr, uint32_t color,
              const Vector3& p1, const Vector3& p2, const Vector3& p3)
   : state_(0u), attr_(attr), color_(color)
  {
    vlistLocal_[0] = p1;
    vlistLocal_[1] = p2;
    vlistLocal_[2] = p3;

    vlistTrans_[0] = p1;
    vlistTrans_[1] = p2;
    vlistTrans_[2] = p3;
  }

  enum TransMode
  {
    kLocalOnly,
    kTransOnly,
    kLocalToTrans
  };
  int transformByMatrix(const Matrix<4, 4>& mt, TransMode mode);
  void worldToCamera(const Camera& camera);
  void cameraToPerspective(const Camera& camera);
  void perspectiveToScreen(const Camera& camera);
  void draw(VideoSystem& videoSys);
  void reset()
  {
    memcpy(vlistTrans_, vlistLocal_, sizeof(vlistTrans_));
  }

 private:
  uint32_t state_;
  uint32_t attr_;
  uint32_t color_;

  Vector3 vlistLocal_[3];
  Vector3 vlistTrans_[3];
};

}

#endif
