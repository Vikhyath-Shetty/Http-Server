#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include "server.h"

int main(int argc, char* argv[]){
  uint16_t port = atoi(argv[1]);
  if (argc != 2 || port == 0)
  {
    fprintf(stderr, "\nUsage: ./[name|a].exe <PORT>");
    exit(EXIT_FAILURE);
  }
  start_server(port);
  close_server();
  return 0;
}