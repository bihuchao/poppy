// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include <math.h>

#include "Camera.h"
#include "MathUtil.h"

namespace poppy
{

Camera::Camera(uint32_t attr, const Vector3& pos,
       const EulerAngles& dir, const Vector3& target,
       float fovH, float fovV, float nearClipZ,
       float farClipZ, float viewPortWidth, float viewPortHeight)
  :attr_(attr), state_(0u), pos_(pos), dir_(dir), u_(1.0f, 0.0f, 0.0f),
   v_(0.0f, 1.0f, 0.0f), n_(0.0f, 0.0f, 1.0f), target_(target),
   fovH_(fovH), fovV_(fovV), nearClipZ_(nearClipZ), farClipZ_(farClipZ),
   viewPortWidth_(viewPortWidth), viewPortHeight_(viewPortHeight),
   aspectRatio_(viewPortWidth / viewPortHeight)
{
  viewPlaneWidth_ = 2.0f;
  viewPlaneHeight_ = 2.0f / aspectRatio_;

  float tanFovDiv2 = tan(degToRad(fovH/2.0f));
  viewDistH_ = (0.5 * viewPlaneWidth_) / tanFovDiv2;

  tanFovDiv2 = tan(degToRad(fovV/2.0f));
  viewDistV_ = (0.5 * viewPlaneHeight_) / tanFovDiv2;
}

Vector3 Camera::transformCameraToPer(const Vector3& pos)
{
  Vector3 ret;

  ret.x = viewDistH_ * pos.x / pos.z;
  ret.y = viewDistV_ * pos.y / pos.z;
  ret.z = pos.z;

  return ret;
}

Vector3 Camera::transformPerToScreen(const Vector3& pos)
{
  Vector3 ret = pos;

  //先根据视平面和屏幕的比例进行一次缩放
  ret.x = ret.x * viewPortWidth_ / viewPlaneWidth_;
  ret.x += viewPortWidth_ / 2.0f;

  ret.y = ret.y * viewPortHeight_ / viewPlaneHeight_;
  ret.y += viewPortHeight_ / 2.0f;
  ret.y = -ret.y + viewPortHeight_ - 1;

  ret.z = pos.z;

  return ret;
}

Vector3 Camera::transformWorldToCamera(const Vector3& pos)
{
  return pos * worldToCamera_;
}

void Camera::buildCameraMatrixByEuler()
{
  //旋转部分
  worldToCamera_ = dir_.getWorldToObjectMatrix();
  //平移部分
  worldToCamera_.setItem(4, 1, -pos_.x);
  worldToCamera_.setItem(4, 2, -pos_.y);
  worldToCamera_.setItem(4, 3, -pos_.z);
}

void Camera::buildCameraMatrixByUNV(enum UvnMode mode)
{
  if (mode == kUvnModeSpherical)
  {
    EulerAngles tmpDir = dir_;
    tmpDir.bank = 0.0f;
    Matrix<4, 4> tmpMatrix = tmpDir.getObjectToWorldMatrix();

    n_.init(0.0f, 0.0f, 1.0f);
    n_ = n_ * tmpMatrix;

    //计算target
    tmpMatrix.setItem(4, 1, pos_.x);
    tmpMatrix.setItem(4, 2, pos_.y);
    tmpMatrix.setItem(4, 3, pos_.z);

    target_.init(0.0f, 0.0f, 1.0f);
    target_ = target_ * tmpMatrix;
  }
  else
  {
    n_ = target_ - pos_;
    n_.normalize();
  }

  v_.init(0.0f, 1.0f, 0.0f);
  u_ = crossProduct(v_, n_);

  v_ = crossProduct(n_, u_);

  u_.normalize();
  v_.normalize();
}

}
