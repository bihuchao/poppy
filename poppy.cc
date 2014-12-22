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
#include "Camera.h"
#include "MathUtil.h"

using namespace poppy;

int main(int argc, char *argv[])
{
  float t1 = 1 / cos(degToRad(30.0));
  float t2 = 2 * cos(degToRad(30.0)) - t1;
  float t3 = t1 * cos(degToRad(30.0));

  Vector3 point1(0, t1, 5.0f);
  Vector3 point2(-t3, -t2, 5.0f);
  Vector3 point3(t3, -t2, 5.0f);

  Camera camera(0, Vector3(0.0f, 0.0f, 0.0f),
                EulerAngles(degToRad(10.0f), degToRad(-10.0f), degToRad(0.0f)),
                Vector3(0.0f, 0.0f, 0.0f), 90.0f, 90.0f, 0.0f,
                0.0f, 640.0f, 640.0f);
  camera.buildCameraMatrixByEuler();
  Matrix<4, 4> worldToCamera = camera.getMatrixWorldToCamera();

  int width = 640;
  int height = 640;

  VideoSystemSDL videoSys;
  videoSys.createWindow(width, height, 32);

  SDL_Event event;
  while (1)
  {
    videoSys.fillSecondary(0u);

    Vector3 tmp1 = point1;
    Vector3 tmp2 = point2;
    Vector3 tmp3 = point3;

    tmp1 = tmp1 * worldToCamera;
    tmp2 = tmp2 * worldToCamera;
    tmp3 = tmp3 * worldToCamera;

    tmp1 = camera.transformCameraToPer(tmp1);
    tmp2 = camera.transformCameraToPer(tmp2);
    tmp3 = camera.transformCameraToPer(tmp3);

    tmp1 = camera.transformPerToScreen(tmp1);
    tmp2 = camera.transformPerToScreen(tmp2);
    tmp3 = camera.transformPerToScreen(tmp3);

    videoSys.lockSecondary();

    videoSys.drawLine(tmp1.x, tmp1.y, tmp2.x, tmp2.y, 255);
    videoSys.drawLine(tmp2.x, tmp2.y, tmp3.x, tmp3.y, 255);
    videoSys.drawLine(tmp3.x, tmp3.y, tmp1.x, tmp1.y, 255);

    videoSys.unlockSecondary();

    videoSys.flipDisplay();

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

