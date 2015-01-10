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
      : primary_(NULL),
        secondary_(NULL),
        width_(0),
        height_(0),
        bitDepth_(0),
        pitchPrimary_(0),
        pitchSecondary_(0),
        lockedPrimaryBuf_(NULL),
        lockedSecondaryBuf_(NULL) { }

  virtual int createWindow(int width, int height, int bitDepth) = 0;
  virtual int lockPrimary();
  virtual int unlockPrimary();
  virtual int lockSecondary();
  virtual int unlockSecondary();
  virtual int fillSecondary(uint32_t color);
  virtual int fillPrimary(uint32_t color);
  virtual int flipDisplay();

  void drawPixel(int x, int y, uint32_t color);
  int drawLine(float x1, float y1, float x2, float y2, uint32_t color);
  int drawRectangle(float x, float y, float w, float h, uint32_t color);
  int drawRectangleSolid(float x, float y, float w, float h, uint32_t color);
  int width() const { return width_; }
  int height() const { return height_; }

  virtual ~VideoSystem() { }
 protected:
  FrameBuffer *primary_;
  FrameBuffer *secondary_;
  int width_;
  int height_;
  int bitDepth_;

 private:
  int lockFrameBufferComon(bool isPrimary);
  int unlockFrameBufferComon(bool isPrimary);

  int pitchPrimary_;
  int pitchSecondary_;

  uint8_t *lockedPrimaryBuf_;
  uint8_t *lockedSecondaryBuf_;

};

}

#endif

