// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include <algorithm>

#include "FrameBuffer.h"
#include "Logger.h"

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

  Line2 line(x1, y1, x2, y2);


  int cx1 = x1;

  int cy1 = y1;
  int cx2 = x2;
  int cy2 = y2;

  int ret = line.clip(width_, height_, &cx1, &cy1, &cx2, &cy2);
  if (ret == 0)
  {
    LOG_ERROR("line is not in window!\n");
    return -1;
  }

  Line2 drawLine(cx1, cy1, cx2, cy2);
  if (drawLine.vLine())
  {
    drawVLine(buf, cy1, cy2, cx1, color);
    return 0;
  }
  else if (drawLine.hLine())
  {
    drawHLine(buf, cx1, cx2, cy1, color);
    return 0;
  }

  drawDiagonal(buf, cx1, cy1, cx2, cy2, color);
  return 0;
}

int FrameBuffer::drawVLine(uint8_t *buf, int y1, int y2, int x, uint32_t color)
{
  int start = std::min(y1, y2);
  int end = std::max(y1, y2);

  for (int y = start; y <= end; y++)
  {
    putPixel(buf, x, y, color);
  }

  return 0;
}

int FrameBuffer::drawHLine(uint8_t *buf, int x1, int x2, int y, uint32_t color)
{
  int start = std::min(x1, x2);
  int end = std::max(x1, x2);

  for (int x = start; x <= end; x++)
  {
    putPixel(buf, x, y, color);
  }

  return 0;
}

int FrameBuffer::drawDiagonal(uint8_t *buf, int x1, int y1, int x2,
                              int y2, uint32_t color)
{
  int start = std::min(x1, x2);
  int end = std::max(x1, x2);
  Line2 line(x1, y1, x2, y2);

  for (int x = start; x <= end; x++)
  {
    int y;
    line.getY(x, &y);

    putPixel(buf, x, y, color);
  }

  start = std::min(y1, y2);
  end = std::max(y1, y2);
  for (int y = start; y <= end; y++)
  {
    int x;
    line.getX(y, &x);
    putPixel(buf, x, y, color);
  }
  return 0;
}

}

