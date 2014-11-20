// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include "FrameBuffer.h"

namespace poppy
{

void FrameBuffer::initFmtSizeMap()
{
  fmtSizeMap[PIXEL_FORMAT8]       = 1; 
  fmtSizeMap[PIXEL_FORMAT555]     = 2; 
  fmtSizeMap[PIXEL_FORMAT565]     = 2; 
  fmtSizeMap[PIXEL_FORMAT888]     = 3; 
  fmtSizeMap[PIXEL_FORMAT8888]    = 4; 
}

int FrameBuffer::getPixelSizeByFmt(PixelFormat fmt)
{
  std::map<PixelFormat, int>::iterator it =
    fmtSizeMap.find(fmt);

  return (it != fmtSizeMap.end()) ? it->second : -1;
}

}

