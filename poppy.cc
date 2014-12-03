#include <stdio.h>
#include <string.h>

#include "SDL/SDL.h"

#include "video/Bitmap.h"
#include "video/FrameBuffer.h"
#include "logger/Logger.h"
#include "video/FrameBufferSDL.h"

using namespace poppy;

int main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_EVERYTHING);
  //setLogLevel(INFO);

  SDL_Surface *screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);

  int x, y;
  uint32_t yellow;

  x = screen->w / 2;
  y = screen->h / 2;
  yellow = SDL_MapRGB(screen->format, 0xff, 0x00, 0x00);

  FrameBufferSDL sdlFrameBuf(screen, true);
  uint8_t *buf = NULL;
  int pitch = 0;

  sdlFrameBuf.lockFrameBuffer(&buf, &pitch);
  sdlFrameBuf.putPixel(buf, x, y, yellow);
  sdlFrameBuf.unlockFrameBuffer(buf);
  
  sdlFrameBuf.fill(yellow);
  //SDL_Flip(screen);

  //handing event
  SDL_Event event;
  while (SDL_WaitEvent(&event)) 
  {
    LOG_INFO("Get a event: %d\n", event.type);
    if (event.type == SDL_QUIT) 
    {
      LOG_INFO("Break from event loop!\n");
      break;
    }
  }

  SDL_Quit();

  return 0;
}

