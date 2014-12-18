#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "SDL/SDL.h"

#include "video/Bitmap.h"
#include "video/FrameBuffer.h"
#include "logger/Logger.h"
#include "video/FrameBufferSDL.h"
#include "video/VideoSystemSDL.h"
#include "math/Matrix.h"

using namespace poppy;

#define PI  (3.1415926f)
#define DEG_TO_RAD(x) (PI * x / 180.0)

Vector3 transformViewToScreen(int width, int height, const Vector3& view)
{
  Vector3 ret = view;
  ret.x += width / 2.0f;
  ret.y += height / 2.0f;

  ret.y = -ret.y + height - 1;

  return ret;
}

Vector3 transformCameraToView(float d, const Vector3& camera)
{
  Vector3 ret;
  ret.x = d * camera.x / camera.z;
  ret.y = d * camera.y / camera.z;
  ret.z = camera.z;

  return ret;
}

int main(int argc, char *argv[])
{
  float t1 = 200 / cos(DEG_TO_RAD(30.0));
  float t2 = 400 * cos(DEG_TO_RAD(30.0)) - t1;
  float t3 = t1 * cos(DEG_TO_RAD(30.0));

  Vector3 point1(0, t1, 0);
  Vector3 point2(-t3, -t2, 0);
  Vector3 point3(t3, -t2, 0);

  int width = 640;
  int height = 640;
  float d = 320;

  VideoSystemSDL videoSys;
  videoSys.createWindow(width, height, 32);

  SDL_Event event;
  float theta = 0.0f;
  while (1)
  {
    videoSys.fillSecondary(0u);

    Matrix<3, 3> matrix;
    matrix.setItem(1, 1, cos(DEG_TO_RAD(theta)));
    matrix.setItem(1, 2, 0);
    matrix.setItem(1, 3, -sin(DEG_TO_RAD(theta)));

    matrix.setItem(2, 1, 0);
    matrix.setItem(2, 2, 1);
    matrix.setItem(2, 3, 0);

    matrix.setItem(3, 1, sin(DEG_TO_RAD(theta)));
    matrix.setItem(3, 2, 0);
    matrix.setItem(3, 3, cos(DEG_TO_RAD(theta)));

    Vector3 tmp1 = point1 * matrix;
    Vector3 tmp2 = point2 * matrix;
    Vector3 tmp3 = point3 * matrix;

    tmp1.z = 720;
    tmp2.z = 720;
    tmp3.z = 720;

    tmp1 = transformCameraToView(d, tmp1);
    tmp2 = transformCameraToView(d, tmp2);
    tmp3 = transformCameraToView(d, tmp3);

    tmp1 = transformViewToScreen(width, height, tmp1);
    tmp2 = transformViewToScreen(width, height, tmp2);
    tmp3 = transformViewToScreen(width, height, tmp3);

    videoSys.lockSecondary();

    uint32_t color = 255;
    videoSys.drawLine(tmp1.x, tmp1.y, tmp2.x, tmp2.y, color);
    videoSys.drawLine(tmp2.x, tmp2.y, tmp3.x, tmp3.y, color);
    videoSys.drawLine(tmp3.x, tmp3.y, tmp1.x, tmp1.y, color);

    videoSys.unlockSecondary();

    videoSys.flipDisplay();

    theta += 1.0f;
    SDL_Delay(10);

    if (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        break;
      }
    }

  }
  return 0;
}

