// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include "FrameBufferSDL.h"
#include "Logger.h"

namespace poppy
{

FrameBufferSDL::FrameBufferSDL(SDL_Surface *surface, bool primary)
  :FrameBuffer(surface->w, surface->h, surface->pitch,
      getPixelFmtSurface(surface)), 
   surface_(surface), primary_(primary)
{
}

PixelFormat FrameBufferSDL::getPixelFmtSurface(SDL_Surface *surface)
{
  if (surface->format->BitsPerPixel == 32)
  {
    return PIXEL_FORMAT8888; 
  }

  return PIXEL_FORMAT_NUM;
}

int FrameBufferSDL::lockFrameBuffer(uint8_t **pbuffer, int *ppitch)
{
  if (SDL_MUSTLOCK(surface_))
  {
    if (SDL_LockSurface(surface_) < 0) 
    {
      LOG_ERROR("lock buffer error!\n");
      return -1; 
    }
  }
  
  *pbuffer = (uint8_t *)surface_->pixels;
  return 0;
}

int FrameBufferSDL::unlockFrameBuffer(uint8_t *buffer)
{
  if (SDL_MUSTLOCK(surface_))
  {
    SDL_UnlockSurface(surface_); 
  }
  
  if (primary_)
  {
    SDL_Flip(surface_); 
  }

  return 0;
}

}

