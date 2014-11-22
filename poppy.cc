#include <stdio.h>
#include <string.h>

#include "video/FrameBufferOfMem.h"
#include "video/Bitmap.h"
#include "logger/Logger.h"

int main(int argc, char *argv[])
{
  poppy::Bitmap bitmap;
  bitmap.loadFromBmpFile(argv[1]);

  bitmap.dumpFileHeader();
  bitmap.dumpInfoHeader();

  bitmap.storeToBmpFile(argv[2]);

  setLogLevel(poppy::TRACE);
  //poppy::disableDebugInfo();
  LOG_TRACE("Hello world\n");
  LOG_DEBUG("Hello world\n");
  LOG_INFO("Hello world\n");
  LOG_WARN("Hello world\n");
  LOG_ERROR("Hello world\n");
  LOG_FATAL("Hello world\n");

  poppy::enableDebugInfo();
  LOG_TRACE("22 Hello world\n");
  LOG_DEBUG("22 Hello world\n");
  LOG_INFO("22 Hello world\n");
  LOG_WARN("22 Hello world\n");
  LOG_ERROR("22 Hello world\n");
  LOG_FATAL("22 Hello world\n");

  return 0;
}

