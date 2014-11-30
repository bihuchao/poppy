// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include "FrameBuffer.h"

namespace poppy
{

void FrameBuffer::initFmtSizeMap()
{
  fmtSizeMap[PIXEL_FORMAT8888]    = 4; 
}

int FrameBuffer::getPixelSizeByFmt(PixelFormat fmt)
{
  std::map<PixelFormat, int>::iterator it =
    fmtSizeMap.find(fmt);

  return (it != fmtSizeMap.end()) ? it->second : -1;
}

uint32_t FrameBuffer::getPixelCommon(uint8_t *buffer, int x, 
    int y, int pitch, int sizepix)
{
  uint8_t *ppixel = buffer + y * pitch + x * sizepix;

  switch (sizepix)
  {
    case 1: 
      return *ppixel;
    case 2:
      return *(uint16_t *)ppixel;
    case 3:
      return ppixel[0] | ppixel[1] << 8 | ppixel[2] << 16;
    case 4:
      return *(uint32_t *)ppixel;
    default:
      return 0;
  }
}

void FrameBuffer::putPixelCommon(uint8_t *buffer, int x, int y, 
      int pitch, int sizepix, uint32_t pixel)
{
  uint8_t *ppixel = buffer + y * pitch + x * sizepix;

  switch (sizepix)
  {
    case 1: 
      *ppixel = (uint8_t)pixel;
      break;
    case 2:
      *(uint16_t *)ppixel = (uint8_t)pixel;
      break;
    case 3:
      ppixel[0] = pixel & 0xff;
      ppixel[1] = (pixel >> 8) & 0xff;
      ppixel[2] = (pixel >> 16) & 0xff;
      break;
    case 4:
      *(uint32_t*)ppixel = pixel;
      break;
    default:
      break;
  }

  return;
}

uint32_t FrameBuffer::getPointPosition(int x, int y, int w, int h)
{
  uint32_t position = 0u;
  int maxX = w - 1;
  int maxY = h - 1;

  if (y < 0)
  {
    position |= kClipCodeN;
  }
  else if (y > maxY)
  {
    position |= kClipCodeS; 
  }
  else if (x < 0)
  {
    position |= kClipCodeW; 
  }
  else if (x > maxX)
  {
    position |= kClipCodeE; 
  }
  
  return position;
}

uint32_t FrameBuffer::getClipedLinePoint(int w, int h, 
    uint32_t pos, int ox, int oy, int *px, int *py)
{
  switch (pos)
  {
    case kClipCodeC: 
      break;
    case kClipCodeN:
      break;
  }

  return 0;
}

int FrameBuffer::clipLine(int w, int h, int *px1, int *py1,
        int *px2, int *py2)
{
  uint32_t p1Code = getPointPosition(*px1, *py1, w, h);
  uint32_t p2Code = getPointPosition(*px2, *py2, w, h);

  //两个点的连线不经过窗口
  if (p1Code & p2Code)
  {
    return 0; 
  }

  //两个点都在窗口内部
  if (p1Code == kClipCodeC && p2Code == kClipCodeC)
  {
    return 1; 
  }


  return 1;
}

}

