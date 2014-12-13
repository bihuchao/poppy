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
  Matrix<5, 3> matrix1("matrix.txt");
  Matrix<3, 5> matrix2("matrix.txt");
  Matrix<5, 5> matrix3 = matrix1 * matrix2;

  matrix3.dump();
  return 0;
}

