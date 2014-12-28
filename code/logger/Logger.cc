// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#include "Logger.h"

namespace poppy
{

#if 0
char *LogLevelStr[] =
{
  "TRACE ",
  "DEBUG ",
  "INFO  ",
  "WARN  ",
  "ERROR ",
  "FATAL "
};

const char *getLogLevelStr(LogLevel level)
{
  return LogLevelStr[level];
}
#endif

LogLevel g_logLevel = WARN;

bool g_enabeDebugInfo = true;

}

