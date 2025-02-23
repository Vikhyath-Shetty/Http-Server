#include <stdio.h>
#include "util.h"
#include "socket.h"

SOCKET init_socket(uint16_t port)
{

  WSADATA wsa;
  if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
  {
    error_exit("Failed to initialize winsock", 0);
  }
  printf("\nWinsock initialized successfully");

  SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (server_socket == INVALID_SOCKET)
  {
    error_exit("Socket creation failed", 1);
  }

  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  memset(&address.sin_zero, 0, 8);

  if (bind(server_socket, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR)
  {
    error_exit("Socket binding failed", 1);
  }

  if (listen(server_socket, 5) == SOCKET_ERROR)
  {
    error_exit("Failed to start server", 1);
  }

  return server_socket;
}

void close_server(SOCKET server_socket)
{
  if (closesocket(server_socket) == SOCKET_ERROR)
    fprintf(stderr, "\nFailed to close server: %d", WSAGetLastError());
  WSACleanup();
}