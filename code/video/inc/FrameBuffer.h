// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_VIDEO_FRAMEBUFFER_H
#define POPPY_VIDEO_FRAMEBUFFER_H

#include <stdint.h>
#include <map>

namespace poppy
{
enum PixelFormat
{
  PIXEL_FORMAT8888,
  PIXEL_FORMAT_NUM
};

class FrameBuffer
{
 public:
  FrameBuffer(int32_t width = 0, int32_t height = 0, int32_t pitch = 0,
              PixelFormat pixfmt = PIXEL_FORMAT_NUM)
      : width_(width),
        height_(height),
        pitch_(pitch),
        pixfmt_(pixfmt)
  {
    initFmtSizeMap();
    sizepix_ = getPixelSizeByFmt(pixfmt_);
  }

  int getPixelSizeByFmt(PixelFormat fmt);

  virtual ~FrameBuffer() { }
  virtual int lockFrameBuffer(uint8_t **pbuffer, int *ppitch) = 0;
  virtual int unlockFrameBuffer(uint8_t *buffer) = 0;
  virtual int fill(uint32_t color) = 0;
  virtual int flip(const FrameBuffer* frameBuf) = 0;

  uint32_t getPixel(uint8_t *buf, int x, int y)
  {
    return getPixelCommon(buf, x, y, pitch_, sizepix_);
  }
  void putPixel(uint8_t *buf, int x, int y, uint32_t pixel)
  {
    putPixelCommon(buf, x, y, pitch_, sizepix_, pixel);
  }

  int drawLine(uint8_t *buf, int x1, int y1, int x2, int y2, uint32_t color);

  static uint32_t getPixelCommon(uint8_t *buffer, int x, int y, int pitch,
                                 int sizepix);
  static void putPixelCommon(uint8_t *buffer, int x, int y, int pitch,
                             int sizepix, uint32_t pixel);
 private:
  int32_t width_;
  int32_t height_;
  int32_t pitch_;
  PixelFormat pixfmt_;
  int32_t sizepix_;

  std::map<PixelFormat, int> fmtSizeMap;
  void initFmtSizeMap();

  int drawVLine(uint8_t *buf, int y1, int y2, int x, uint32_t color);
  int drawHLine(uint8_t *buf, int x1, int x2, int y, uint32_t color);
};

}

#endif

