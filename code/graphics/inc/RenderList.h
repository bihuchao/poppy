// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_GRAPHICS_RENDERLIST_H
#define POPPY_GRAPHICS_RENDERLIST_H

#include <list>

#include "PolygonFull.h"
#include "Camera.h"

namespace poppy
{

class RenderList
{
 public:
  RenderList(uint32_t attr = 0u): state_(0u), attr_(attr) { }
  void insert(const PolygonFull& poly) { polyList_.push_back(poly); }

  void transformByMatrix(const Matrix<4, 4>& mt,
                        PolygonFull::TransMode mode);

  void worldToCamera(const Camera& camera);
  void cameraToPerspective(const Camera& camera);
  void perspectiveToScreen(const Camera& camera);
  void draw(VideoSystem& videoSys);
  void drawSolid(VideoSystem& videoSys);
  void reset();
 private:
  uint32_t state_;
  uint32_t attr_;

  std::list<PolygonFull> polyList_;
};

}

#endif
