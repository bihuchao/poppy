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
   : state_(kPolyStateActive), attr_(attr), color_(color)
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

  static const uint32_t kPolyStateActive      = 0x0001;
  static const uint32_t kPolyStateClipped     = 0x0002;
  static const uint32_t kPolyStateBackface    = 0x0004;

  static const uint32_t kPolyAttr2Side        = 0x0001;
  static const uint32_t kPolyAttrTransparent  = 0x0002;
  static const uint32_t kPolyAttr8BitColor    = 0x0004;
  static const uint32_t kPolyAttrRgb16        = 0x0008;
  static const uint32_t kPolyAttrRgb24        = 0x0010;

  static const uint32_t kPolyAttrShadeModePure      = 0x0020;
  static const uint32_t kPolyAttrShadeModeFlat      = 0x0040;
  static const uint32_t kPolyAttrShadeModeGouraud   = 0x0080;
  static const uint32_t kPolyAttrShadeModePhong     = 0x0100;

  int transformByMatrix(const Matrix<4, 4>& mt, uint32_t mode);
  void worldToCamera(const Camera& camera);
  void cameraToPerspective(const Camera& camera);
  void perspectiveToScreen(const Camera& camera);
  void draw(VideoSystem& videoSys);
  void drawSolid(VideoSystem& videoSys);
  void reset()
  {
    memcpy(vlistTrans_, vlistLocal_, sizeof(vlistTrans_));
  }

 private:
  static bool PointCompareY(const Vector3& lhs, const Vector3& rhs) 
  { return lhs.y < rhs.y; }

  uint32_t state_;
  uint32_t attr_;
  uint32_t color_;

  Vector3 vlistLocal_[3];
  Vector3 vlistTrans_[3];
};

}

#endif
