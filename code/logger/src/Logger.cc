// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: dingcongjun (dingcj)

#ifdef WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdint.h>

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

LogLevel g_logLevel = POPPY_WARN;

bool g_enabeDebugInfo = true;

uint16_t g_recvUdpPortBase = 30000;
int g_sendLogSocket = -1;

void sendLogMessage(const char *msg, int len, uint16_t port)
{
  if (g_sendLogSocket == -1)
  {
#ifdef WIN32
    WSADATA wsadata;
    if(WSAStartup(MAKEWORD(1,1),&wsadata)==SOCKET_ERROR)
   {
     fprintf(stderr, "WSAStartup() fail - %s:%d\n",
             __FILE__, __LINE__);
     return;
   }
#endif
    g_sendLogSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (g_sendLogSocket == -1)
    {
      fprintf(stderr, "Create socket error - %s:%d\n",
              __FILE__, __LINE__);
      return;
    }
  }

  struct sockaddr_in dst;
  memset(&dst, 0, sizeof(dst));
  dst.sin_family = AF_INET;
  dst.sin_port = htons(port);
  dst.sin_addr.s_addr = inet_addr("127.0.0.1");
  int ret = sendto(g_sendLogSocket, msg, len, 0,
                   (const struct sockaddr *)(&dst), sizeof(dst));
  if (ret != len)
  {
    fprintf(stderr, "Send log message error %d - %s:%d\n", ret,
            __FILE__, __LINE__);
    g_sendLogSocket = -1;
    return;
  }

  return;
}

}

