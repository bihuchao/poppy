// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifndef POPPY_LOGGER_LOGGER_H
#define POPPY_LOGGER_LOGGER_H

#include <stdio.h>
#include <stdint.h>

#include <string>

namespace poppy
{

enum LogLevel
{
  POPPY_TRACE,
  POPPY_DEBUG,
  POPPY_INFO,
  POPPY_WARN,
  POPPY_ERROR,
  POPPY_FATAL,
  NUM_LOG_LEVELS,
};

extern LogLevel g_logLevel;
extern bool g_enabeDebugInfo;
extern uint16_t g_recvUdpPortBase;
const char *getLogLevelStr(LogLevel level);
void sendLogMessage(const char *msg, int len, uint16_t port);

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

inline void setRecvUdpPortBase(uint16_t port)
{
  g_recvUdpPortBase = port;
}

#define LOG_TRACE(fmt, args...) \
  do                            \
  {                             \
    if (poppy::g_enabeDebugInfo && (poppy::logLevel() <= poppy::POPPY_TRACE)) \
    { \
      char buf[1024]; \
      std::string tmp("%s%s:%d - "); \
      tmp = tmp + fmt; \
      int num = snprintf(buf, sizeof(buf), tmp.c_str(), "TRACE ", \
                         __FILE__, __LINE__, ##args); \
      fprintf(stderr, "%s", buf);\
      poppy::sendLogMessage(buf, num, g_recvUdpPortBase); \
    } \
  } while (0)

#define LOG_DEBUG(fmt, args...) \
  do                            \
  {                             \
    if (poppy::g_enabeDebugInfo && (poppy::logLevel() <= poppy::POPPY_DEBUG)) \
    { \
      char buf[1024]; \
      std::string tmp("%s%s:%d - "); \
      tmp = tmp + fmt; \
      int num = snprintf(buf, sizeof(buf), tmp.c_str(), "DEBUG ", \
                         __FILE__, __LINE__, ##args); \
      fprintf(stderr, "%s", buf);\
      poppy::sendLogMessage(buf, num, g_recvUdpPortBase + 1); \
    } \
  } while (0)

#define LOG_INFO(fmt, args...) \
  do                            \
  {                             \
    if (poppy::g_enabeDebugInfo && poppy::logLevel() <= poppy::POPPY_INFO) \
    { \
      char buf[1024]; \
      std::string tmp("%s%s:%d - "); \
      tmp = tmp + fmt; \
      int num = snprintf(buf, sizeof(buf), tmp.c_str(), "INFO  ", \
                         __FILE__, __LINE__, ##args); \
      fprintf(stderr, "%s", buf);\
      poppy::sendLogMessage(buf, num, g_recvUdpPortBase + 2); \
    } \
  } while (0)

#define LOG_WARN(fmt, args...) \
  do                            \
  {                             \
    if (poppy::g_enabeDebugInfo)       \
    {\
      char buf[1024]; \
      std::string tmp("%s%s:%d - "); \
      tmp = tmp + fmt; \
      int num = snprintf(buf, sizeof(buf), tmp.c_str(), "WARN  ", \
                         __FILE__, __LINE__, ##args); \
      fprintf(stderr, "%s", buf);\
      poppy::sendLogMessage(buf, num, g_recvUdpPortBase + 3); \
    }\
  } while (0)

#define LOG_ERROR(fmt, args...) \
  do                            \
  {                             \
    if (poppy::g_enabeDebugInfo)       \
    { \
      char buf[1024];\
      std::string tmp("%s%s:%d - "); \
      tmp = tmp + fmt; \
      int num = snprintf(buf, sizeof(buf), tmp.c_str(), "ERROR ", \
                         __FILE__, __LINE__, ##args); \
      fprintf(stderr, "%s", buf);\
      poppy::sendLogMessage(buf, num, g_recvUdpPortBase + 4); \
    } \
  } while (0)

#define LOG_FATAL(fmt, args...) \
  do                            \
  {                             \
    if (poppy::g_enabeDebugInfo)       \
    { \
      char buf[1024]; \
      std::string tmp("%s%s:%d - "); \
      tmp = tmp + fmt; \
      int num = snprintf(buf, sizeof(buf), tmp.c_str(), "FATAL ", \
                         __FILE__, __LINE__, ##args); \
      fprintf(stderr, "%s", buf);\
      poppy::sendLogMessage(buf, num, g_recvUdpPortBase + 5); \
    } \
  } while (0)

}

#endif

