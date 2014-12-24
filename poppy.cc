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
#include "PolygonFull.h"

using namespace poppy;

int main(int argc, char *argv[])
{
  float t1 = 1 / cos(degToRad(30.0));
  float t2 = 2 * cos(degToRad(30.0)) - t1;
  float t3 = t1 * cos(degToRad(30.0));

  Vector3 point1(0, t1, 5.0f);
  Vector3 point2(-t3, -t2, 5.0f);
  Vector3 point3(t3, -t2, 5.0f);
  PolygonFull polygon(0u, 255u, point1, point2, point3);

  int width = 640;
  int height = 480;

  Camera camera(0, Vector3(0.0f, 0.0f, 3.0f),
                EulerAngles(degToRad(0.0f), degToRad(0.0f), degToRad(0.0f)),
                Vector3(0.0f, 0.0f, 0.0f), 90.0f, 0.0f, 0.0f, width, height);
  camera.buildCameraMatrixByEuler();

  VideoSystemSDL videoSys;
  videoSys.createWindow(width, height, 32);

  SDL_Event event;
  while (1)
  {
    videoSys.fillSecondary(0u);

    polygon.reset();
    polygon.worldToCamera(camera);
    polygon.cameraToPerspective(camera);
    polygon.perspectiveToScreen(camera);

    videoSys.lockSecondary();

    polygon.draw(videoSys);

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

