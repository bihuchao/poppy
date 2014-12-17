#include <stdio.h>
#include <string.h>

#include "SDL/SDL.h"

#include "video/Bitmap.h"
#include "video/FrameBuffer.h"
#include "logger/Logger.h"
#include "video/FrameBufferSDL.h"
#include "video/VideoSystemSDL.h"
#include "math/Matrix.h"

using namespace poppy;

int main(int argc, char *argv[])
{
  Matrix<4, 4> matrix1("matrix.txt");
  Vector3 tmp1(1.0f, 2.0f, 3.0f);
  Vector3 tmp2 = tmp1 * matrix1;

  printf("x: %f, y: %f, z: %f\n", tmp2.x, tmp2.y, tmp2.z);
  return 0;
}

