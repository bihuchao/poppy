#include <algorithm>

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "SDL/SDL.h"

#include "FrameBuffer.h"
#include "Logger.h"
#include "FrameBufferSDL.h"
#include "VideoSystemSDL.h"
#include "Matrix.h"
#include "Camera.h"
#include "MathUtil.h"
#include "PolygonFull.h"
#include "RenderList.h"
#include "Object.h"

using namespace poppy;

// e > 0  : e = k + e - 1
// e <= 0 : e = k + e
int drawLine(VideoSystem& videoSys, int x1, int y1,
             int x2, int y2, uint32_t color)
{
  bool exchangeXY = false;
  if (abs(y2 - y1) > abs(x2 - x1))
  {
    exchangeXY = true;
    std::swap(x1, y1);
    std::swap(x2, y2);
  }

  float k = abs(y2 - y1) / (float)abs(x2 - x1);
  float e = k - 0.5;
  int iy = (y2 - y1) > 0 ? 1 : -1;
  int ix = (x2 - x1) > 0 ? 1 : -1;
  for (int x = x1, y = y1; x != (x2 + 1); x += ix)
  {
    if (exchangeXY)
    {
      videoSys.drawPixel(y, x, color);
    }
    else
    {
      videoSys.drawPixel(x, y, color);
    }

    if (e > 0)
    {
      y += iy;
      e += k - 1;
    }
    else
    {
      e += k;
    }
  }
  return 0;
}

int main(int argc, char *argv[])
{
  int width = 640;
  int height = 640;
  VideoSystemSDL videoSys;
  videoSys.createWindow(width, height, 32, false);

  SDL_Event event;
  while (true)
  {
    for (int dsty = 1; dsty < 640; ++dsty)
    {
      videoSys.fillSecondary(0u);
      videoSys.lockSecondary();
      videoSys.drawLine(0, 0, 639, dsty,255);

      if (SDL_PollEvent(&event))
      {
        if (event.type == SDL_QUIT)
        {
          goto RET;
        }
      }
      SDL_Delay(10);
      videoSys.unlockSecondary();
      videoSys.flipDisplay();
    }

    for (int dstx = 1; dstx < 640; ++dstx)
    {
      videoSys.fillSecondary(0u);
      videoSys.lockSecondary();
      videoSys.drawLine(0, 0, dstx, 639, 255);

      if (SDL_PollEvent(&event))
      {
        if (event.type == SDL_QUIT)
        {
          goto RET;
        }
      }
      SDL_Delay(10);
      videoSys.unlockSecondary();
      videoSys.flipDisplay();
    }

    for (int dsty = 638; dsty > 0; --dsty)
    {
      videoSys.fillSecondary(0u);
      videoSys.lockSecondary();
      videoSys.drawLine(639, dsty, 0, 639, 255);

      if (SDL_PollEvent(&event))
      {
        if (event.type == SDL_QUIT)
        {
          goto RET;
        }
      }
      SDL_Delay(10);
      videoSys.unlockSecondary();
      videoSys.flipDisplay();
    }

    for (int dstx = 1; dstx < 640; ++dstx)
    {
      videoSys.fillSecondary(0u);
      videoSys.lockSecondary();
      videoSys.drawLine(dstx, 0, 0, 639, 255);

      if (SDL_PollEvent(&event))
      {
        if (event.type == SDL_QUIT)
        {
          goto RET;
        }
      }
      SDL_Delay(10);
      videoSys.unlockSecondary();
      videoSys.flipDisplay();
    }

    if (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        goto RET;
      }
    }
  }

RET:
  return 0;
}

