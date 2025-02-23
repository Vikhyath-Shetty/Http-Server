#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <winsock2.h>
#include "util.h"

void error_exit(char *message, SOCKET client_soc, SOCKET server_soc, exit_flag e_flag)
{
  fprintf(stderr, "\n%s:%d", message, WSAGetLastError());
  if (e_flag & CLIENT_SOCKET)
    closesocket(client_soc);
  if (e_flag & SERVER_SOCKET)
    closesocket(server_soc);
  if (e_flag & WINSOCK_CLEAN)
    WSACleanup();
  exit(EXIT_FAILURE);
}