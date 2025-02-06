#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "server.h"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "Usage: ./[a|name].exe <port>");
    return EXIT_FAILURE;
  }

  char *endptr;
  long port = strtol(argv[1], &endptr, 10);
  if (*endptr != '\0' || port <= 0 || port > 65535)
  {
    fprintf(stderr, "\nPort number is invalid, the range is 1-65535");
    return EXIT_FAILURE;
  }
  int serverStatus = start_server((uint16_t)port);
  return serverStatus;
}