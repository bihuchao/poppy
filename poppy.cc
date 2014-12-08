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

  videoSys.createWindow(640, 640, 32);

#if 1
  uint32_t color = 0 + (255 << 8) + (0 << 16);
  videoSys.lockSecondary();
  //videoSys.drawLine(-1, -1, 780, 780, color);
  //videoSys.drawLine(-1, 0, 655, 0, color);
  //videoSys.drawLine(-1000, 639, 10000, 639, color);
  //videoSys.drawLine(0, 1000, 0, -1000, color);
  //videoSys.drawLine(639, -1000, 639, 1000, color);
  videoSys.drawLine(639, -200, 0, 639, color);
  //videoSys.fillSecondary(color);
  videoSys.unlockSecondary();

  videoSys.flipDisplay();

  SDL_Event event;
  while (SDL_WaitEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      LOG_INFO("Break from event loop!\n");
      break;
    }
  }
#endif

#if 0
  //handing event
  SDL_Event event;
  uint32_t color;
  bool quit = false;
  bool show = false;
  while (!quit)
  {
    if (!show)
    {
      videoSys.lockSecondary();
      for (int x = 10; x < 640; x += 10)
      {
        uint8_t r = rand() % 255;
        uint8_t g = rand() % 255;
        uint8_t b = rand() % 255;
        color = b + (g << 8) + (r << 16);
        videoSys.drawLine(0, 0, x, 639, color);
      }
      videoSys.drawLine(0, 0, 639, 639, color);

      for (int y = 10; y < 640; y += 10)
      {
        uint8_t r = rand() % 255;
        uint8_t g = rand() % 255;
        uint8_t b = rand() % 255;
        color = b + (g << 16) + (r << 24);
        videoSys.drawLine(0, 0, 639, y, color);
      }

      videoSys.unlockSecondary();

      videoSys.flipDisplay();
      show = true;
    }

    if (SDL_PollEvent(&event))
    {
      LOG_INFO("Get a event: %d\n", event.type);
      if (event.type == SDL_QUIT)
      {
        LOG_INFO("Break from event loop!\n");
        quit = true;
      }
    }
  }
#endif
  SDL_Quit();

  return 0;
}

