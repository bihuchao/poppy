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
#include "RenderList.h"
#include "PolygonFull.h"

namespace poppy
{

class Polygon
{
 public:
  Polygon() { memset(this, 0, sizeof(*this)); }

  Polygon(uint32_t attr, uint32_t color,
          std::vector<Vector3>* pvlist,
          int p1, int p2, int p3)
    : state_(PolygonFull::kPolyStateActive), attr_(attr), color_(color),
      pvlist_(pvlist)
  { vert_[0] = p1, vert_[1] = p2, vert_[2] = p3; }

  operator PolygonFull() const;

  uint32_t state_;
  uint32_t attr_;
  uint32_t color_;

  std::vector<Vector3>* pvlist_;
  int vert_[3];
};

class Object
{
 public:
  Object(const char *plgfile, uint32_t attr);
  Object(const Object& rhs);

  Object& operator=(const Object& rhs);
  int insertToRenderList(RenderList *renderList);
  int transformByMatrix(const Matrix<4, 4>& mt,
                        PolygonFull::TransMode mode);
  int transformToWorld(const Vector3& pos, const EulerAngles* angles,
                       PolygonFull::TransMode mode);
  void removeBackFaces(const Camera& camera);
  int cull(const Camera& camera, uint32_t cullFlag);

  enum CullObjectFlag
  {
    kCullObjectZPlane = 1,
    kCullObjectXPlane = 2,
    kCullObjectYPlane = 4
  };

  enum ObjectState
  {
    kObjectStateActive  = 1,
    kObjectStateVisible = 2,
    kObjectStateCulled  = 4,
  };
 private:
  uint32_t attr_;
  uint32_t state_;

  float avgRadius_;
  float maxRadius_;

  Vector3 ux_, vy_, nz_;

  Vector3 pos_;
  std::string name_;
  uint32_t id_;
  std::vector<Vector3> vlistLocal_;
  std::vector<Vector3> vlistTrans_;

  std::vector<Polygon> polyList_;

  void moveNotByMatrix(const Vector3& pos, PolygonFull::TransMode mode);
  void computeMaxRadius();
};

}

#endif
