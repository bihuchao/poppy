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
       float fov, float nearClipZ, float farClipZ,
       float viewPortWidth, float viewPortHeight)
  :attr_(attr), state_(0u), pos_(pos), dir_(dir), u_(1.0f, 0.0f, 0.0f),
   v_(0.0f, 1.0f, 0.0f), n_(0.0f, 0.0f, 1.0f), target_(target),
   fov_(fov), nearClipZ_(nearClipZ), farClipZ_(farClipZ),
   viewPortWidth_(viewPortWidth), viewPortHeight_(viewPortHeight),
   aspectRatio_(viewPortWidth / viewPortHeight)
{
  viewPlaneWidth_ = 2.0f;
  viewPlaneHeight_ = 2.0f / aspectRatio_;

  float tanFovDiv2 = tan(degToRad(fov/2.0f));
  viewDist_ = (0.5 * viewPlaneWidth_) / tanFovDiv2;
}

Vector3 Camera::transformCameraToPer(const Vector3& pos) const
{
  Vector3 ret;

  ret.x = viewDist_ * pos.x / pos.z;
  ret.y = viewDist_ * pos.y / pos.z;
  ret.z = pos.z;

  return ret;
}

Vector3 Camera::transformPerToScreen(const Vector3& pos) const
{
  Vector3 ret = pos;

  //先根据视平面和屏幕的比例进行一次缩放
  float alpha = 0.5 * viewPortWidth_ - 0.5;
  float beta = 0.5 * viewPortHeight_ - 0.5;

  ret.x = alpha + alpha * pos.x;
  ret.y = beta - beta * pos.y;

  ret.z = pos.z;

  return ret;
}

Vector3 Camera::transformWorldToCamera(const Vector3& pos) const
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

  buildPerspectiveMatrix();
  buildScreenMatrix();
}

void Camera::buildCameraMatrixByUNV(enum UvnMode mode)
{
  if (mode == kUvnModeSpherical)
  {
    EulerAngles tmpDir = dir_;
    tmpDir.bank = 0.0f;
    Matrix<4, 4> tmpMatrix = tmpDir.getObjectToWorldMatrix();

    //n表示方向，不需要平移
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

  //构建世界坐标到相机坐标的转换矩阵
  worldToCamera_.zero();
  worldToCamera_.setItem(1, 1, u_.x);
  worldToCamera_.setItem(2, 1, u_.y);
  worldToCamera_.setItem(3, 1, u_.z);

  worldToCamera_.setItem(1, 2, v_.x);
  worldToCamera_.setItem(2, 2, v_.y);
  worldToCamera_.setItem(3, 2, v_.z);

  worldToCamera_.setItem(1, 3, n_.x);
  worldToCamera_.setItem(2, 3, n_.y);
  worldToCamera_.setItem(3, 3, n_.z);

  //平移部分
  worldToCamera_.setItem(4, 1, -pos_.x);
  worldToCamera_.setItem(4, 2, -pos_.y);
  worldToCamera_.setItem(4, 3, -pos_.z);

  worldToCamera_.setItem(4, 4, 1);

  buildPerspectiveMatrix();
  buildScreenMatrix();
}

void Camera::buildPerspectiveMatrix()
{
  cameraToPer_.zero();

  cameraToPer_.setItem(1, 1, viewDist_);
  cameraToPer_.setItem(2, 2, viewDist_);
  cameraToPer_.setItem(3, 3, 1.0f);
  cameraToPer_.setItem(3, 4, 1.0f);
}

void Camera::buildScreenMatrix()
{
  float alpha = 0.5 * viewPortWidth_ - 0.5;
  float beta = 0.5 * viewPortHeight_ - 0.5;

  perToScreen_.zero();
  perToScreen_.setItem(1, 1, alpha);
  perToScreen_.setItem(2, 2, -beta);
  perToScreen_.setItem(3, 1, alpha);
  perToScreen_.setItem(3, 2, beta);
  perToScreen_.setItem(3, 3, 1);
  perToScreen_.setItem(4, 4, 1);
}

}
