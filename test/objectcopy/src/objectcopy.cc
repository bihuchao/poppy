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

  //Object tank("./plg/tank1.plg", 0u);
  Object tower("./plg/tower1.plg", 0u);
  tower.scale(Vector3(1.0, 2.0, 1.0), PolygonFull::kLocalOnly);

  VideoSystemSDL videoSys;
  videoSys.createWindow(width, height, 32, false);

  Object tmpTower = tower;
  SDL_Event event;
  float deg = 0.0f;
  while (1)
  {
    videoSys.fillSecondary(0x0);

    Camera camera(0, Vector3(-570.0, 40.0, 1680.0f),
                  EulerAngles(degToRad(0.0f), degToRad(0.0f), degToRad(0.0f)),
                  Vector3(0.0f, 0.0f, 1600.0f), 120.0f, 100.0f, 12000.0f, width, height);
    camera.buildCameraMatrixByEuler();
    //camera.buildCameraMatrixByUNV(Camera::kUvnModeSimple);

    mainRenderList.reset();

    tmpTower = tower;
    EulerAngles angles(degToRad(deg), 0.0f, 0.0f);
    tmpTower.transformToWorld(Vector3(-570.0, 0, 1965), &angles, PolygonFull::kLocalToTrans);
    tmpTower.cull(camera, Object::kCullObjectXPlane | Object::kCullObjectYPlane | Object::kCullObjectZPlane);
    tmpTower.removeBackFaces(camera);
    tmpTower.insertToRenderList(&mainRenderList);

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
    //deg += 1.0f;
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

