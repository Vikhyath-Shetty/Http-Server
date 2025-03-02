#ifndef REQUEST_H
#define REQUEST_H

#include<stddef.h>
typedef struct{
  char* request_line[3];
  char* headers[];
}Req_prop;

Req_prop* parseRequest(char* request);

#endif