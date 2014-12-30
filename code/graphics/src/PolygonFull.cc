// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include "PolygonFull.h"
#include "Logger.h"

namespace poppy
{

int PolygonFull::transformByMatrix(const Matrix<4, 4>& mt, uint32_t mode)
{
  Vector3 resault;
  int ret = 0;

  if (!(state_ & kPolyStateActive)
      || (state_ & kPolyStateClipped)
      || (state_ & kPolyStateBackface))
  {
    return 0;
  }

  switch (mode)
  {
    case kLocalOnly:
      for (int i = 0; i < 3; i++)
      {
        resault = vlistLocal_[i] * mt;
        vlistLocal_[i] = resault;
      }
      break;
    case kTransOnly:
      for (int i = 0; i < 3; i++)
      {
        resault = vlistTrans_[i] * mt;
        vlistTrans_[i] = resault;
      }
      break;
    case kLocalToTrans:
      for (int i = 0; i < 3; i++)
      {
        vlistTrans_[i] =vlistLocal_[i] * mt;
      }
      break;
    default:
      LOG_ERROR("transform mode error - %d\n", mode);
      ret = -1;
      break;
  }
  return ret;
}

void PolygonFull::worldToCamera(const Camera& camera)
{
  if (!(state_ & kPolyStateActive)
      || (state_ & kPolyStateClipped)
      || (state_ & kPolyStateBackface))
  {
    return;
  }

  for (int i = 0; i < 3; i++)
  {
    vlistTrans_[i] = camera.transformWorldToCamera(vlistTrans_[i]);
  }
}

void PolygonFull::cameraToPerspective(const Camera& camera)
{
  if (!(state_ & kPolyStateActive)
      || (state_ & kPolyStateClipped)
      || (state_ & kPolyStateBackface))
  {
    return;
  }

  for (int i = 0; i < 3; i++)
  {
    vlistTrans_[i] = camera.transformCameraToPer(vlistTrans_[i]);
  }
}

void PolygonFull::perspectiveToScreen(const Camera& camera)
{
  if (!(state_ & kPolyStateActive)
      || (state_ & kPolyStateClipped)
      || (state_ & kPolyStateBackface))
  {
    return;
  }

  for (int i = 0; i < 3; i++)
  {
    vlistTrans_[i] = camera.transformPerToScreen(vlistTrans_[i]);
  }
}

void PolygonFull::draw(VideoSystem& videoSys)
{
  if (!(state_ & kPolyStateActive)
      || (state_ & kPolyStateClipped)
      || (state_ & kPolyStateBackface))
  {
    return;
  }

  videoSys.drawLine(vlistTrans_[0].x, vlistTrans_[0].y,
                    vlistTrans_[1].x, vlistTrans_[1].y, color_);
  videoSys.drawLine(vlistTrans_[1].x, vlistTrans_[1].y,
                    vlistTrans_[2].x, vlistTrans_[2].y, color_);
  videoSys.drawLine(vlistTrans_[2].x, vlistTrans_[2].y,
                    vlistTrans_[0].x, vlistTrans_[0].y, color_);
}

}
