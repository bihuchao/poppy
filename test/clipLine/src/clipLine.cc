#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>

#include "Line2.h"

using namespace poppy;

int main(int argc, char *argv[])
{
  int x1 = 845, y1 = 599;
  int x2 = 849, y2 = 598;

  Line2 line(x1, y1, x2, y2);
  line.clip(800, 600, &x1, &y1, &x2, &y2);

  printf("%d %d %d %d\n", x1, y1, x2, y2);
  return 0;
}

