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

const int kNumOfTanks = 24;
const int kNumOfTowers = 96;
const int kUniverseRadius = 4000;
const int kPointSize = 200;
const int kNumPointsX = 2 * kUniverseRadius / kPointSize;
const int kNumPointsZ = 2 * kUniverseRadius / kPointSize;
const int kNumPoints  = kNumPointsX * kNumPointsZ;

const int kTankSpeed = 15;

int main(int argc, char *argv[])
{
  int width = 800;
  int height = 600;
  VideoSystemSDL videoSys;
  videoSys.createWindow(width, height, 32);

  Vector3 cameraPos(0, 40, 0);
  EulerAngles cameraDir(0, 0, 0);
  Vector3 cameraTarget(0, 0, 0);
  Camera camera(0, cameraPos,
                EulerAngles(degToRad(0.0f), degToRad(0.0f), degToRad(0.0f)),
                cameraTarget, 120.0f, 100.0f, 12000.0f, width, height);
  camera.buildCameraMatrixByEuler();
  //camera.buildCameraMatrixByUNV(Camera::kUvnModeSimple);

  Object objTank("./plg/tank2.plg", 0u);
  objTank.scale(Vector3(0.75, 0.75, 0.75), PolygonFull::kLocalOnly);

  Object objPlayer("./plg/tank3.plg", 0u);
  objPlayer.scale(Vector3(0.75, 0.75, 0.75), PolygonFull::kLocalOnly);

  Object objTower("./plg/tower1.plg", 0u);
  objTower.scale(Vector3(1.0, 2.0, 1.0), PolygonFull::kLocalOnly);

  Object objMarker("./plg/marker1.plg", 0u);
  objMarker.scale(Vector3(3.0, 3.0, 3.0), PolygonFull::kLocalOnly);

  std::vector<Vector3> tanksPos;
  std::vector<EulerAngles> tanksDir;
  for (int i = 0; i < kNumOfTanks; i++)
  {
    Vector3 vec(randRange(-kUniverseRadius, kUniverseRadius), 0,
                randRange(-kUniverseRadius, kUniverseRadius));
    EulerAngles dir(randRange(0, 360), 0, 0);
    tanksPos.push_back(vec);
    tanksDir.push_back(dir);
  }

  std::vector<Vector3> towersPos;
  for (int i = 0; i < kNumOfTowers; i++)
  {
    Vector3 vec(randRange(-kUniverseRadius, kUniverseRadius), 0,
                randRange(-kUniverseRadius, kUniverseRadius));
    towersPos.push_back(vec);
  }

  RenderList mainRenderList;
  SDL_Event event;
  while (true)
  {
    mainRenderList.reset();

    videoSys.fillSecondary(0x0);

    videoSys.lockSecondary();

    videoSys.drawRectangleSolid(0, 0, width, height / 2, (140 << 8) | (192));
    videoSys.drawRectangleSolid(0, height / 2, width, height / 2, (103 << 16) | (62 << 8) | (3));

    videoSys.unlockSecondary();

    for (int i = 0; i < kNumOfTanks; i++)
    {
      Object tmp = objTank;
      tmp.transformToWorld(tanksPos[i], &tanksDir[i],
                           PolygonFull::kLocalToTrans);
      tmp.cull(camera, Object::kCullObjectXPlane | Object::kCullObjectYPlane
                | Object::kCullObjectZPlane);
      tmp.insertToRenderList(&mainRenderList);
    }

    for (int i = 0; i < kNumOfTowers; i++)
    {
      Object tmp = objTower;
      tmp.transformToWorld(towersPos[i], NULL,
                           PolygonFull::kLocalToTrans);
      tmp.cull(camera, Object::kCullObjectXPlane | Object::kCullObjectYPlane
                | Object::kCullObjectZPlane);
      tmp.insertToRenderList(&mainRenderList);
    }

    Vector3 pos(cameraPos.x, cameraPos.y - 70, cameraPos.z + 300);
    Object tmpPlayer = objPlayer;
    tmpPlayer.transformToWorld(pos, NULL, PolygonFull::kLocalToTrans);
    tmpPlayer.insertToRenderList(&mainRenderList);

    srand(13);
    for (int i = 0; i < kNumPointsX; i++)
    {
      for (int j = 0; j < kNumPointsZ; j++)
      {
        Object tmp = objMarker;
        Vector3 vec(randRange(-100, 100)-kUniverseRadius + i * kPointSize, tmp.getMaxRadius(),
                    randRange(-100, 100)-kUniverseRadius + j * kPointSize);
        tmp.transformToWorld(vec, NULL, PolygonFull::kLocalToTrans);
        tmp.cull(camera, Object::kCullObjectXPlane | Object::kCullObjectYPlane
                  | Object::kCullObjectZPlane);
        tmp.insertToRenderList(&mainRenderList);
      }
    }

    mainRenderList.worldToCamera(camera);
    mainRenderList.cameraToPerspective(camera);
    mainRenderList.perspectiveToScreen(camera);

    videoSys.lockSecondary();

    mainRenderList.draw(videoSys);

    videoSys.unlockSecondary();

    videoSys.flipDisplay();

    SDL_Delay(10);
    if (SDL_PollEvent(&event))
    {
      int tankSpeed = kTankSpeed;
      if (event.type == SDL_QUIT)
      {
        break;
      }
      else if (event.type == SDL_KEYDOWN)
      {
        if (event.key.keysym.sym == SDLK_SPACE)
        {
          tankSpeed = kTankSpeed * 5;
        }
        if (event.key.keysym.sym == SDLK_LEFT)
        {

        }
        if (event.key.keysym.sym == SDLK_RIGHT)
        {

        }
        if (event.key.keysym.sym == SDLK_UP)
        {
          cameraPos.z += tankSpeed;
        }
        if (event.key.keysym.sym == SDLK_DOWN)
        {
          cameraPos.z -= tankSpeed;
        }
      }
      camera.setPos(cameraPos);
      camera.buildCameraMatrixByEuler();
    }
  }

  return 0;
}

