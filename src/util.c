#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

int error_exit(char *message, uint8_t cleanup)
{
  fprintf(stderr, "\n%s:%d", message, WSAGetLastError());
  if (cleanup)
  {
    WSACleanup();
  }
  exit(EXIT_FAILURE);
}