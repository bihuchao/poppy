// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include "RenderList.h"
#include "Logger.h"

namespace poppy
{

void RenderList::transformByMatrix(const Matrix<4, 4>& mt,
                                  PolygonFull::TransMode mode)
{
  int ret = 0;

  for (std::vector<PolygonFull>::iterator iter = polyList_.begin();
        iter != polyList_.end(); ++iter)
  {
    ret = iter->transformByMatrix(mt, mode);
    if (ret != 0)
    {
      LOG_ERROR("render list transform error - %d!\n", ret);
    }
  }
}

void RenderList::worldToCamera(const Camera& camera)
{
  for (std::vector<PolygonFull>::iterator iter = polyList_.begin();
        iter != polyList_.end(); ++iter)
  {
    iter->worldToCamera(camera);
  }
}

void RenderList::cameraToPerspective(const Camera& camera)
{
  for (std::vector<PolygonFull>::iterator iter = polyList_.begin();
        iter != polyList_.end(); ++iter)
  {
    iter->cameraToPerspective(camera);
  }
}

void RenderList::perspectiveToScreen(const Camera& camera)
{
  for (std::vector<PolygonFull>::iterator iter = polyList_.begin();
        iter != polyList_.end(); ++iter)
  {
    iter->perspectiveToScreen(camera);
  }
}

void RenderList::draw(VideoSystem& videoSys)
{
  for (std::vector<PolygonFull>::iterator iter = polyList_.begin();
        iter != polyList_.end(); ++iter)
  {
    iter->draw(videoSys);
  }
}

void RenderList::drawSolid(VideoSystem& videoSys)
{
  for (std::vector<PolygonFull>::iterator iter = polyList_.begin();
        iter != polyList_.end(); ++iter)
  {
    iter->drawSolid(videoSys);
  }
}

void RenderList::reset()
{
  polyList_.clear();

  state_ = 0u;
  attr_ = 0u;
}

}
