// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_VIDEO_VIDEOSYSTEM_H
#define POPPY_VIDEO_VIDEOSYSTEM_H

#include <stdint.h>
#include <stdlib.h>
#include "FrameBuffer.h"

namespace poppy
{

class VideoSystem
{
  public:
    VideoSystem()
      :primary_(NULL),
      secondary_(NULL),
      lockedPrimaryBuf_(NULL),
      lockedSecondaryBuf_(NULL),
      width_(0), height_(0), bitDepth_(0) { }

    virtual int flip() = 0;
    virtual int createWindow(int width, int height, int bitDepth) = 0;
    virtual int lockPrimary();
    virtual int unlockPrimary();
    virtual int lockSecondary();
    virtual int unlockSecondary();
    //virtual int fillSecondary(uint32_t color);
    //virtual int fillPrimary(uint32_t color);
    
    virtual ~VideoSystem() { }
  private:
    int lockFrameBufferComon(bool isPrimary);
    int unlockFrameBufferComon(bool isPrimary);

    FrameBuffer *primary_;
    FrameBuffer *secondary_;
    int pitchPrimary_;
    int pitchSecondary_;

    uint8_t *lockedPrimaryBuf_;
    uint8_t *lockedSecondaryBuf_;
    
    int width_;
    int height_;
    int bitDepth_;
};

}

#endif

