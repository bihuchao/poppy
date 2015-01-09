#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>

#include "Line.h"

using namespace poppy;

int main(int argc, char *argv[])
{
  Line line1(0.0f, 0.0f, 900.0f, 900.0f);

  int x1, y1;
  int x2, y2;
  int width = 640, height = 480;
  int ret = 0;

  ret = line1.clip(width, height, &x1, &y1, &x2, &y2);
  printf("%d %d %d %d %d\n", x1, y1, x2, y2, ret);

  Line line2(0.0, -100, 0.0, 1000);
  ret = line2.clip(width, height, &x1, &y1, &x2, &y2);
  printf("%d %d %d %d %d\n", x1, y1, x2, y2, ret);

  Line line3(639, -100, 639, 1000);
  ret = line3.clip(width, height, &x1, &y1, &x2, &y2);
  printf("%d %d %d %d %d\n", x1, y1, x2, y2, ret);

  Line line4(639, 0, 639, 0);
  ret = line4.clip(width, height, &x1, &y1, &x2, &y2);
  printf("%d %d %d %d %d\n", x1, y1, x2, y2, ret);

  Line line5(-639, 0, 639, 0);
  ret = line5.clip(width, height, &x1, &y1, &x2, &y2);
  printf("%d %d %d %d %d\n", x1, y1, x2, y2, ret);

  Line line6(0, 479, 10000, 479);
  ret = line6.clip(width, height, &x1, &y1, &x2, &y2);
  printf("%d %d %d %d %d\n", x1, y1, x2, y2, ret);

  return 0;
}

