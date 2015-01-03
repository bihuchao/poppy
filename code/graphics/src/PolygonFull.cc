// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include <algorithm>

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

void PolygonFull::drawSolid(VideoSystem& videoSys)
{
  Vector3 vecTmp[3];
  vecTmp[0] = vlistTrans_[0];
  vecTmp[1] = vlistTrans_[1];
  vecTmp[2] = vlistTrans_[2];

  std::sort(&vecTmp[0], &vecTmp[3], PointCompareY);

  float dxyLeft, dxyRight;
  float xLeft, xRight;
  if (vecTmp[0].y == vecTmp[1].y)
  {
    dxyLeft = (vecTmp[2].x - vecTmp[0].x) / (vecTmp[2].y - vecTmp[0].y);
    dxyRight = (vecTmp[2].x - vecTmp[1].x) / (vecTmp[2].y - vecTmp[1].y);
    xLeft = vecTmp[0].x;
    xRight = vecTmp[1].x;
    for (float y = vecTmp[0].y; y <= vecTmp[2].y; y++)
    {
      videoSys.drawLine(xLeft + 0.5, y + 0.5, xRight + 0.5, y + 0.5, color_); 
      xLeft += dxyLeft;
      xRight += dxyRight;
    }
    return;
  }
  else if (vecTmp[1].y == vecTmp[2].y)
  {
    dxyLeft = (vecTmp[1].x - vecTmp[0].x) / (vecTmp[1].y - vecTmp[0].y);
    dxyRight = (vecTmp[2].x - vecTmp[0].x) / (vecTmp[2].y - vecTmp[0].y);
    xLeft = vecTmp[0].x;
    xRight = vecTmp[0].x;
    for (float y = vecTmp[0].y; y <= vecTmp[2].y; y++)
    {
      videoSys.drawLine(xLeft + 0.5, y + 0.5, xRight + 0.5, y + 0.5, color_); 
      xLeft += dxyLeft;
      xRight += dxyRight;
    }
    return;
  }

  Line2 line(vecTmp[0].x + 0.5, vecTmp[0].y + 0.5,
             vecTmp[2].x + 0.5, vecTmp[2].y + 0.5);

  float y3 = vecTmp[1].y;
  int x3 = 0.0;
  line.getX(y3, &x3);

  PolygonFull poly1(attr_, color_, vecTmp[1], 
                    vecTmp[2], Vector3(x3, y3, 0));
  PolygonFull poly2(attr_, color_, vecTmp[1], 
                    vecTmp[0], Vector3(x3, y3, 0));
  poly1.drawSolid(videoSys);
  poly2.drawSolid(videoSys);

  return;
}

}
