#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <algorithm>

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

int main(int argc, char *argv[])
{
  RenderList mainRenderList;

  int width = 800;
  int height = 600;

  Object tank("./plg/tank1.plg", 0u);
  Object cube("./plg/cube1.plg", 0u);

  VideoSystemSDL videoSys;
  videoSys.createWindow(width, height, 32, false);

  Object tmpCube = cube;
  SDL_Event event;
  float deg = 0.0f;
  while (1)
  {
    videoSys.fillSecondary(0x0);

    Camera camera(0, Vector3(0.0, 0.0, 0.0f),
                  EulerAngles(degToRad(0.0f), degToRad(45.0f), degToRad(0.0f)),
                  Vector3(0.0f, 0.0f, 1600.0f), 90.0f, 5.0f, 5000.0f, width, height);
    //camera.buildCameraMatrixByEuler();
    camera.buildCameraMatrixByUNV(Camera::kUvnModeSimple);

    mainRenderList.reset();
    tmpCube = tank;

    EulerAngles angles(degToRad(deg), 0.0f, 0.0f);
    tmpCube.transformToWorld(Vector3(0, 0, 1500), &angles, PolygonFull::kLocalToTrans);
    tmpCube.insertToRenderList(&mainRenderList);

    mainRenderList.worldToCamera(camera);
    mainRenderList.cameraToPerspective(camera);
    mainRenderList.perspectiveToScreen(camera);

    videoSys.lockSecondary();

    mainRenderList.drawSolid(videoSys);

    videoSys.unlockSecondary();

    videoSys.flipDisplay();

    if (deg >= 360)
    {
      deg = 0.0f;
    }
    deg += 1.0f;
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

