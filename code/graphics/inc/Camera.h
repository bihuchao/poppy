// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_GRAPHICS_CAMERA_H
#define POPPY_GRAPHICS_CAMERA_H

#include <stdint.h>

#include "EulerAngles.h"
#include "Vector3.h"
#include "Matrix.h"

namespace poppy
{

class Camera
{
 public:
  Camera(uint32_t attr, const Vector3& pos,
         const EulerAngles& dir, const Vector3& target,
         float nearClipZ, float farClipZ, float fov,
         float viewPortWidth, float viewPortHeiht);

  Vector3 transformPerToScreen(const Vector3& pos) const;
  Vector3 transformCameraToPer(const Vector3& pos) const;
  Vector3 transformWorldToCamera(const Vector3& pos) const;

  Matrix<4, 4> getMatrixWorldToCamera() const { return worldToCamera_; }
  Matrix<4, 4> getMatrixCameraToPer() const { return cameraToPer_; }
  Matrix<4, 4> getMatrixPerToScreen() const { return perToScreen_; }

  void buildCameraMatrixByEuler();
  Vector3 getPos() const { return pos_; }
  void setPos(const Vector3& pos) { pos_ = pos; }
  float getFarClipZ() const { return farClipZ_; }
  float getNearClipZ() const { return nearClipZ_; }
  float getViewDist() const { return viewDist_; }
  float viewPlaneWidth() const { return viewPlaneWidth_; }
  float viewPlaneHeight() const { return viewPlaneHeight_; }

  enum CameraMode
  {
    kCamModeEuler,
    kCamModeUvn
  };

  enum UvnMode
  {
    kUvnModeSpherical,
    kUvnModeSimple,
  };
  void buildCameraMatrixByUNV(enum UvnMode mode);
 private:
  uint32_t attr_;
  uint32_t state_;

  Vector3 pos_;
  EulerAngles dir_;

  Vector3 u_;
  Vector3 v_;
  Vector3 n_;
  Vector3 target_;

  float viewDist_;

  float fov_;

  float nearClipZ_;
  float farClipZ_;

  float viewPlaneWidth_;
  float viewPlaneHeight_;

  float viewPortWidth_;
  float viewPortHeight_;

  float aspectRatio_;

  Matrix<4, 4> worldToCamera_;
  Matrix<4, 4> cameraToPer_;
  Matrix<4, 4> perToScreen_;

  void buildPerspectiveMatrix();
  void buildScreenMatrix();
};

}

#endif
