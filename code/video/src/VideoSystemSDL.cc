// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include <stdint.h>
#include <stdlib.h>

#include "VideoSystemSDL.h"
#include "FrameBufferSDL.h"
#include "Logger.h"

namespace poppy
{

int VideoSystemSDL::createWindow(int width, int height, int bitDepth, bool fullscreen)
{
  uint32_t mode = 0;
  mode |= SDL_SWSURFACE;
  if (fullscreen)
  {
    mode |= SDL_FULLSCREEN;
  }

  SDL_Surface *primary = SDL_SetVideoMode(width, height, bitDepth, mode);
  if (primary == NULL)
  {
    LOG_ERROR("SDL_SetVideoMode error\n"); 
    return -1;
  }

  SDL_Surface *secondary = SDL_CreateRGBSurface(SDL_SWSURFACE, primary->w,
      primary->h, primary->format->BitsPerPixel, primary->format->Rmask,
      primary->format->Gmask, primary->format->Bmask, primary->format->Amask);
  if (secondary == NULL)
  {
    LOG_ERROR("SDL_CreateRGBSurface error\n"); 
    return -1;
  }
  
  primary_ = new FrameBufferSDL(primary, true);
  secondary_ = new FrameBufferSDL(secondary, false);
  width_ = width;
  height_ = height;
  bitDepth_ = bitDepth;

  return 0;
}

VideoSystemSDL::~VideoSystemSDL()
{
  if (primary_)
  {
    delete primary_; 
  }

  if (secondary_)
  {
    delete secondary_; 
  }

  SDL_Quit();
}

}
