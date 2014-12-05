#include <stdio.h>
#include <string.h>

#include "SDL/SDL.h"

#include "video/Bitmap.h"
#include "video/FrameBuffer.h"
#include "logger/Logger.h"
#include "video/FrameBufferSDL.h"
#include "video/VideoSystemSDL.h"

using namespace poppy;

int main(int argc, char *argv[])
{
#if 0
  SDL_Init(SDL_INIT_EVERYTHING);
  //setLogLevel(INFO);

  SDL_Surface *screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
  SDL_Surface *bmp = SDL_LoadBMP(argv[1]);
  FrameBufferSDL bmpFrameBuf(bmp, false);

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
  
  //sdlFrameBuf.fill(yellow);
  //SDL_Flip(screen);
  sdlFrameBuf.flip(&bmpFrameBuf); 
#endif

  VideoSystemSDL videoSys;

  videoSys.createWindow(640, 480, 32);
  int x = 0;
  int y = 0;

  for (x = 0; x < 640; x++)
  {
    for (y = 0; y < 480; y++)
    {
      uint8_t r = rand() % 255;
      uint8_t g = rand() % 255;
      uint8_t b = rand() % 255;
      uint32_t color = b + (g << 8) + (r << 16);
      
      //videoSys.lockSecondary();
      videoSys.drawPixel(x, y, color);
      //videoSys.unlockSecondary();
    }
  }

  videoSys.flipDisplay();

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

  return 0;
}

