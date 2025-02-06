#include<stdio.h>
#include "socket.h"

int error_exit(char* message, uint8_t cleanup){
  fprintf(stderr,"\n%s:%d",WSAGetLastError());
  if(cleanup){
    WSACleanup();
  }
  exit(EXIT_FAILURE);
}

SOCKET init_socket(uint16_t port){

  // winsock initialization 
  WSADATA wsa;
  if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
  {
    error_exit("Failed to initialize winsock",0);
  }
  printf("\nWinsock initialized successfully");

  // Socket creation
  SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (server_socket == INVALID_SOCKET)
  {
    fprintf(stderr,"\nSocket creation failed: %d",WSAGetLastError());
    return INVALID_SOCKET;
  }

  // Socket binding
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr("127.0.0.1");
  address.sin_port = htons(port);
  memset(&address.sin_zero, 0, 8);

  if (bind(server_socket, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR)
  {
    fprintf(stderr,"\nSocket binding failed: %d",WSAGetLastError());
    return SOCKET_ERROR;
  }

  // listening for request
  if (listen(server_socket, 5) == SOCKET_ERROR)
  {
    fprintf(stderr,"\nFailed to start server: %d",WSAGetLastError());
    return SOCKET_ERROR;
  }

  return server_socket;
}