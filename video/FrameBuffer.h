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
    FrameBuffer(int32_t pitch = 0, int32_t width = 0, 
        int32_t height = 0, int32_t pixfmt = 0)
      :pitch_(pitch), width_(width), height_(height), pixfmt_(pixfmt) { }
    int getPixelSizeByFmt(PixelFormat fmt);
    virtual ~FrameBuffer() { }
    virtual int lockFrameBuffer(uint8_t **pbuffer, int *ppitch) = 0;
    virtual int unlockFrameBuffer(uint8_t *buffer) = 0;
    
    virtual uint32_t getPixel(uint8_t *buffer, int x, int y);
    virtual void putPixel(uint8_t *buffer, int x, 
        int y, uint32_t pixel);

    static uint32_t getPixelCommon(uint8_t *buffer, int x,
            int y, int pitch, int sizepix);
    static void putPixelCommon(uint8_t *buffer, int x, int y,
            int pitch, int sizepix, uint32_t pixel);
  private:
    int32_t pitch_;
    int32_t width_;
    int32_t height_;
    int32_t pixfmt_;
    int32_t sizepix_;

    std::map<PixelFormat, int> fmtSizeMap;
    void initFmtSizeMap();
};

}

#endif

