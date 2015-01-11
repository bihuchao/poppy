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

int main(int argc, char *argv[])
{
  RenderList mainRenderList;

  int width = 800;
  int height = 600;

  Object tank("./plg/tank1.plg", 0u);

  VideoSystemSDL videoSys;
  videoSys.createWindow(width, height, 32, true);

  SDL_Event event;
  float deg = 0.0f;
  float cx = 0.0f, cy = 0.0f;
  while (1)
  {
    videoSys.fillSecondary(0x0);

    Camera camera(0, Vector3(cx, cy, 0.0f),
                  EulerAngles(degToRad(0.0f), degToRad(45.0f), degToRad(0.0f)),
                  Vector3(0.0f, 0.0f, 1600.0f), 90.0f, 5.0f, 5000.0f, width, height);
    //camera.buildCameraMatrixByEuler();
    camera.buildCameraMatrixByUNV(Camera::kUvnModeSimple);

    mainRenderList.reset();
    for (int i = 0; i < 16; i++)
    {
      Object tmp0 = tank;
      Vector3 pos0(0.0f, 0.0f, 200 * (i + 1));
      tmp0.transformToWorld(pos0, NULL, PolygonFull::kLocalToTrans);
      tmp0.cull(camera, Object::kCullObjectXPlane | Object::kCullObjectYPlane
                | Object::kCullObjectZPlane);
      tmp0.insertToRenderList(&mainRenderList);

      for (int j = 0; j < 16; j++)
      {
        Object tmp1 = tank;
        Vector3 pos1(150 * (j + 1), 0.0f, 200 * (i + 1));
        tmp1.transformToWorld(pos1, NULL, PolygonFull::kLocalToTrans);
        tmp1.cull(camera, Object::kCullObjectXPlane | Object::kCullObjectYPlane
                  | Object::kCullObjectZPlane);
        tmp1.insertToRenderList(&mainRenderList);

        Object tmp2 = tank;
        Vector3 pos2(150 * (-j - 1), 0.0f, 200 * (i + 1));
        tmp2.transformToWorld(pos2, NULL, PolygonFull::kLocalToTrans);
        tmp2.cull(camera, Object::kCullObjectXPlane | Object::kCullObjectYPlane
                  | Object::kCullObjectZPlane);
        tmp2.insertToRenderList(&mainRenderList);
      }
    }

    mainRenderList.worldToCamera(camera);
    mainRenderList.cameraToPerspective(camera);
    mainRenderList.perspectiveToScreen(camera);

    videoSys.lockSecondary();

    mainRenderList.draw(videoSys);

    videoSys.unlockSecondary();

    videoSys.flipDisplay();

    deg += 1.0f;
    if (deg >= 360.0f)
    {
      deg = 0.0f;
    }

    SDL_Delay(10);

    if (SDL_WaitEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        break;
      }
      else if (event.type == SDL_KEYDOWN)
      {
        if (event.key.keysym.sym == SDLK_LEFT)
        {
          cx -= 10.0f;
        }
        else if (event.key.keysym.sym == SDLK_RIGHT)
        {
          cx += 10.0f;
        }
        else if (event.key.keysym.sym == SDLK_UP)
        {
          cy += 10.0f;
        }
        else if (event.key.keysym.sym == SDLK_DOWN)
        {
          cy -= 10.0f;
        }
      }
    }

  }
  return 0;
}

