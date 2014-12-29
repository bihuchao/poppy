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

  //�ȸ�����ƽ�����Ļ�ı�������һ������
  ret.x = ret.x * viewPortWidth_ / viewPlaneWidth_;
  ret.x += viewPortWidth_ / 2.0f;

  ret.y = ret.y * viewPortHeight_ / viewPlaneHeight_;
  ret.y += viewPortHeight_ / 2.0f;
  ret.y = -ret.y + viewPortHeight_ - 1;

  ret.z = pos.z;

  return ret;
}

Vector3 Camera::transformWorldToCamera(const Vector3& pos) const
{
  return pos * worldToCamera_;
}

void Camera::buildCameraMatrixByEuler()
{
  //��ת����
  worldToCamera_ = dir_.getWorldToObjectMatrix();
  //ƽ�Ʋ���
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

    //n��ʾ���򣬲���Ҫƽ��
    n_.init(0.0f, 0.0f, 1.0f);
    n_ = n_ * tmpMatrix;

    //����target
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

  //�����������굽��������ת������
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

  //ƽ�Ʋ���
  worldToCamera_.setItem(4, 1, -pos_.x);
  worldToCamera_.setItem(4, 2, -pos_.y);
  worldToCamera_.setItem(4, 3, -pos_.z);

  worldToCamera_.setItem(4, 4, 1);
}

}
