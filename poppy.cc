#include <stdio.h>
#include <string.h>

#include "video/FrameBufferOfMem.h"
#include "video/Bitmap.h"

int main(int argc, char *argv[])
{
  poppy::Bitmap bitmap;
  bitmap.loadFromBmpFile(argv[1]);

  bitmap.dumpFileHeader();
  bitmap.dumpInfoHeader();

  bitmap.storeToBmpFile(argv[2]);

  return 0;
}

