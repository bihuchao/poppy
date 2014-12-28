#ifdef WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "usage: %s <port>", argv[0]);
    return -1;
  }
  int sockFd = -1;
#ifdef WIN32
  WSADATA wsadata;
  if (WSAStartup(MAKEWORD(1, 1), &wsadata) == SOCKET_ERROR)
  {
    fprintf(stderr, "WSAStartup() fail - %s:%d\n",
    __FILE__, __LINE__);
    return -1;
  }
#endif
  sockFd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockFd == -1)
  {
    fprintf(stderr, "Create socket error - %s:%d\n",
    __FILE__, __LINE__);
#ifdef WIN32
    WSACleanup();
#endif
    return -1;
  }

  struct sockaddr_in local;
  memset(&local, 0, sizeof(local));
  uint16_t port = atoi(argv[1]);
  local.sin_family = AF_INET;
  local.sin_port = htons(port);
  local.sin_addr.s_addr = inet_addr("127.0.0.1");
  int ret = bind(sockFd,(struct sockaddr*)&local,sizeof local);
  if (ret != 0)
  {
    fprintf(stderr, "bind error %d - %s:%d\n", ret,
            __FILE__, __LINE__);
#ifdef WIN32
    //WinsowsÏÂ¹Ø±Õsocket
    closesocket(sockFd);
    WSACleanup();
#else
    close(sockFd);
#endif
  }
  while (1)
  {
    char buf[2048];

    ret = recvfrom(sockFd, buf, sizeof(buf) - 1, 0, NULL, NULL);
    if (ret <= 0)
    {
      fprintf(stderr, "recvfrom error %d - %s:%d\n", ret,
              __FILE__, __LINE__);
      break;
    }
    buf[ret] = '\0';
    fprintf(stderr, "%s", buf);
  }

  return 0;
}

