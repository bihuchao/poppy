#include <stdio.h>
#include <string.h>

#include "SDL/SDL.h"

#include "video/Bitmap.h"
#include "video/FrameBuffer.h"
#include "logger/Logger.h"

using namespace poppy;

int main(int argc, char *argv[])
{
#if 0
  setLogLevel(poppy::TRACE);
  //poppy::disableDebugInfo();
  LOG_TRACE("Hello world\n");
  LOG_DEBUG("Hello world\n");
  LOG_INFO("Hello world\n");
  LOG_WARN("Hello world\n");
  LOG_ERROR("Hello world\n");
  LOG_FATAL("Hello world\n");

  poppy::enableDebugInfo();
  LOG_TRACE("22 Hello world\n");
  LOG_DEBUG("22 Hello world\n");
  LOG_INFO("22 Hello world\n");
  LOG_WARN("22 Hello world\n");
  LOG_ERROR("22 Hello world\n");
  LOG_FATAL("22 Hello world\n");
#endif

  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Surface *screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);

  int x, y;
  uint32_t yellow;

  x = screen->w / 2;
  y = screen->h / 2;
  yellow = SDL_MapRGB(screen->format, 0xff, 0x00, 0x00);

  if (SDL_MUSTLOCK(screen))
  {
    if (SDL_LockSurface(screen) < 0) 
    {
      fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
      return -1;
    }
  }
  
  FrameBuffer::putPixelCommon((uint8_t *)screen->pixels, x, y,
      screen->pitch, screen->format->BytesPerPixel, yellow);

  if ( SDL_MUSTLOCK(screen) ) {
    SDL_UnlockSurface(screen);
  }

  //SDL_Flip(screen);
  SDL_UpdateRect(screen, x, y, 1, 1); 
  SDL_Delay(2000);

  return 0;
}

