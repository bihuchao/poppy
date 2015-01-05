#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "SDL/SDL.h"

#include "Bitmap.h"
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
  /*
  float t1 = 1 / cos(degToRad(30.0));
  float t2 = 2 * cos(degToRad(30.0)) - t1;
  float t3 = t1 * cos(degToRad(30.0));

  Vector3 point1(0, t1, 5.0f);
  Vector3 point2(-t3, -t2, 5.0f);
  Vector3 point3(t3, -t2, 5.0f);
  PolygonFull polygon(0u, 255u, point1, point2, point3);
  */
  RenderList mainRenderList;
  Object cube("./plg/cube2.plg", 0u);

  int width = 640;
  int height = 480;

  Camera camera(0, Vector3(0.0f, 0.0f, 0.0f),
                EulerAngles(degToRad(0.0f), degToRad(0.0f), degToRad(0.0f)),
                Vector3(0.0f, 0.0f, 50.0f), 90.0f, 0.0f, 0.0f, width, height);
  //camera.buildCameraMatrixByEuler();
  camera.buildCameraMatrixByUNV(Camera::kUvnModeSimple);

  VideoSystemSDL videoSys;
  videoSys.createWindow(width, height, 32);

  SDL_Event event;
  float deg = 0.0f;
  while (1)
  {
    videoSys.fillSecondary(0xffffffu);

    //polygon.reset();
    //mainRenderList.insert(polygon);
    mainRenderList.reset();
    EulerAngles revolve(degToRad(deg), 0.0f, 0.0f);

    Object tmp = cube;
    tmp.transformToWorld(Vector3(0.0f, 0.0f, 20.0f), &revolve, PolygonFull::kLocalToTrans);
    tmp.removeBackFaces(camera);
    tmp.insertToRenderList(&mainRenderList);

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

