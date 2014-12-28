// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_VIDEO_FRAMEBUFFERSDL_H
#define POPPY_VIDEO_FRAMEBUFFERSDL_H

#include "SDL/SDL.h"

#include "FrameBuffer.h"
namespace poppy
{

class FrameBufferSDL : public FrameBuffer
{
 public:
  FrameBufferSDL(SDL_Surface *surface, bool primary);

  virtual int lockFrameBuffer(uint8_t **pbuffer, int *ppitch);
  virtual int unlockFrameBuffer(uint8_t *buffer);
  virtual int fill(uint32_t color);
  virtual int flip(const FrameBuffer* frameBuf);
 private:
  PixelFormat getPixelFmtSurface(SDL_Surface *surface);
  SDL_Surface *surface_;
  bool primary_;
};

}

#endif

