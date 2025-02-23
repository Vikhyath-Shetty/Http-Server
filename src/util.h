#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <winsock2.h>
typedef enum
{
  CLIENT_SOCKET = 1 << 0,
  SERVER_SOCKET = 1 << 1,
  WINSOCK_CLEAN = 1 << 2
} exit_flag;

void error_exit(char *message, SOCKET client_soc, SOCKET server_soc, exit_flag e_flag);

#endif