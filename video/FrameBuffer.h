// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include <stdint.h>
#include <map>

namespace poppy
{
enum PixelFormat
{
  PIXEL_FORMAT8 = 0,
  PIXEL_FORMAT555,
  PIXEL_FORMAT565,
  PIXEL_FORMAT888,
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
  private:
    int32_t pitch_;
    int32_t width_;
    int32_t height_;
    int32_t pixfmt_;

    std::map<PixelFormat, int> fmtSizeMap;
    void initFmtSizeMap();
};

}

