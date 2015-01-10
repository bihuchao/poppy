// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include <algorithm>

#include "FrameBuffer.h"
#include "Logger.h"
#include "Line.h"

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

int FrameBuffer::drawLine(uint8_t *buf, int x1, int y1, int x2, int y2, uint32_t color)
{
  //vline
  if (x1 == x2)
  {
    drawVLine(buf, y1, y2, x1, color);
    return 0;
  }

  //hline
  if (y1 == y2)
  {
    drawHLine(buf, x1, x2, y1, color);
    return 0;
  }

  bool exchangeXY = false;
  if (abs(y2 - y1) > abs(x2 - x1))
  {
    exchangeXY = true;
    std::swap(x1, y1);
    std::swap(x2, y2);
  }

  float k = abs(y2 - y1) / (float)abs(x2 - x1);
  float e = k - 0.5;
  int iy = (y2 - y1) > 0 ? 1 : -1;
  int ix = (x2 - x1) > 0 ? 1 : -1;
  for (int x = x1, y = y1; x != (x2 + 1); x += ix)
  {
    if (exchangeXY)
    {
      putPixel(buf, y, x, color);
    }
    else
    {
      putPixel(buf, x, y, color);
    }

    if (e > 0)
    {
      y += iy;
      e += k - 1;
    }
    else
    {
      e += k;
    }
  }

  return 0;
}

int FrameBuffer::drawVLine(uint8_t *buf, int y1, int y2, int x, uint32_t color)
{
  if (y1 > y2)
  {
    std::swap(y1, y2);
  }

  for (int y = y1; y <= y2; y++)
  {
    putPixel(buf, x, y, color);
  }

  return 0;
}

int FrameBuffer::drawHLine(uint8_t *buf, int x1, int x2, int y, uint32_t color)
{
  if (x1 > x2)
  {
    std::swap(x1, x2);
  }

  for (int x = x1; x <= x2; x++)
  {
    putPixel(buf, x, y, color);
  }

  return 0;
}

}

