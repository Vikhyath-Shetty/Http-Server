#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "Usage:./socket.exe <port>");
    exit(EXIT_FAILURE);
  }

  // Initiate winsock dll process
  WSADATA wsa;
  if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
  {
    printf("Failed to initialize winsock : %d", WSAGetLastError());
    exit(EXIT_FAILURE);
  }
  printf("Winsock initialized successfully");
}