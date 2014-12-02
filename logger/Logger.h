// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_LOGGER_LOGGER_H
#define POPPY_LOGGER_LOGGER_H

#include <stdio.h>

namespace poppy
{

enum LogLevel
{
  TRACE,
  DEBUG,
  INFO,
  WARN,
  ERROR,
  FATAL,
  NUM_LOG_LEVELS,
};

extern LogLevel g_logLevel;
extern bool g_enabeDebugInfo;
const char *getLogLevelStr(LogLevel level);

inline LogLevel logLevel()
{
  return g_logLevel;
}

inline void setLogLevel(LogLevel level)
{
  g_logLevel = level;
}

inline void enableDebugInfo()
{
  g_enabeDebugInfo = true;
}

inline void disableDebugInfo()
{
  g_enabeDebugInfo = false;
}

#define LOG_TRACE(fmt, args...) \
  do                            \
  {                             \
    if (poppy::g_enabeDebugInfo && (poppy::logLevel() <= poppy::TRACE)) \
      fprintf(stderr, "%s%s:%d - "fmt, "TRACE ", \
          __FILE__, __LINE__, ##args); \
  } while (0)

#define LOG_DEBUG(fmt, args...) \
  do                            \
  {                             \
    if (poppy::g_enabeDebugInfo && (poppy::logLevel() <= poppy::DEBUG)) \
      fprintf(stderr, "%s%s:%d - "fmt, "DEBUG ", \
          __FILE__, __LINE__, ##args); \
  } while (0)

#define LOG_INFO(fmt, args...) \
  do                            \
  {                             \
    if (poppy::g_enabeDebugInfo && poppy::logLevel() <= poppy::INFO) \
      fprintf(stderr, "%s%s:%d - "fmt, "INFO  ", \
          __FILE__, __LINE__, ##args); \
  } while (0)

#define LOG_WARN(fmt, args...) \
  do                            \
  {                             \
    if (poppy::g_enabeDebugInfo)       \
      fprintf(stderr, "%s%s:%d - "fmt, "WARN  ", \
        __FILE__, __LINE__, ##args); \
  } while (0)

#define LOG_ERROR(fmt, args...) \
  do                            \
  {                             \
    if (poppy::g_enabeDebugInfo)       \
      fprintf(stderr, "%s%s:%d - "fmt, "ERROR ", \
        __FILE__, __LINE__, ##args); \
  } while (0)

#define LOG_FATAL(fmt, args...) \
  do                            \
  {                             \
    if (poppy::g_enabeDebugInfo)       \
      fprintf(stderr, "%s%s:%d - "fmt, "FATAL ", \
        __FILE__, __LINE__, ##args); \
  } while (0)

}

#endif

