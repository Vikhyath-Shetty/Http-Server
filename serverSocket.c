#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

void error(char *message)
{
  errno = WSAGetLastError();
  perror(message);
  WSACleanup();
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "\nUsage:./socket.exe <port>");
    exit(EXIT_FAILURE);
  }

  // winsock initialization
  WSADATA wsa;
  if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
  {
    error("\nWinsock failed to initialize");
  }
  printf("\nWinsock initialized successfully");

  // Socket creation
  SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (server_socket == INVALID_SOCKET)
  {
    error("\nSocket creation failed");
  }
  printf("\nSocket created successfully");

  // Socket binding
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr("127.0.0.1");
  address.sin_port = htons(atoi(argv[1]));
  if (bind(server_socket, (struct sockaddr *)&address, sizeof(address)) != 0)
  {
    error("\nBinding failed");
  }
  printf("\nSocket has been bound");

  // listening for request
  if (listen(server_socket, SOMAXCONN) != 0)
  {
    error("\nFailed to listen");
  }
  printf("\nListening to incoming request at %s", argv[1]);

  //accepting request
  SOCKET new_socket = accept(server_socket,NULL,NULL);
  if(new_socket == INVALID_SOCKET){
    printf("\nFailed to accept connection:%d",WSAGetLastError());
  }
  printf("\nAccepted a client");


  WSACleanup();
  return 0;
}