// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_VIDEO_VIDEOSYSTEMSDL_H
#define POPPY_VIDEO_VIDEOSYSTEMSDL_H

#include "SDL/SDL.h" 
#include "VideoSystem.h"

namespace poppy
{

class VideoSystemSDL : public VideoSystem
{
 public:
  VideoSystemSDL()
  {
    SDL_Init(SDL_INIT_EVERYTHING);
  }

  virtual int createWindow(int width, int height, int bitDepth, bool fullscreen);

  ~VideoSystemSDL();
};

}

#endif

