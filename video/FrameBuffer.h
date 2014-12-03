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
    FrameBuffer(int32_t width = 0, int32_t height = 0, 
        int32_t pitch = 0, PixelFormat pixfmt = PIXEL_FORMAT_NUM)
      :width_(width), height_(height), pitch_(pitch),
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

    static uint32_t getPixelCommon(uint8_t *buffer, int x,
            int y, int pitch, int sizepix);
    static void putPixelCommon(uint8_t *buffer, int x, int y,
            int pitch, int sizepix, uint32_t pixel);

    static uint32_t getPointPosition(int x, int y, int w, int h);
    static uint32_t getClipedLinePoint(int w, int h, uint32_t pos,
        int ox, int oy, int *px, int *py);
    static int clipLine(int w, int h, int *px1, int *py1, 
        int *px2, int *py2);

    const static uint32_t kClipCodeC = 0x00;
    const static uint32_t kClipCodeN = 0x08;
    const static uint32_t kClipCodeS = 0x04;
    const static uint32_t kClipCodeE = 0x02;
    const static uint32_t kClipCodeW = 0x01;
  private:
    int32_t width_;
    int32_t height_;
    int32_t pitch_;
    PixelFormat pixfmt_;
    int32_t sizepix_;

    std::map<PixelFormat, int> fmtSizeMap;
    void initFmtSizeMap();
};

}

#endif

