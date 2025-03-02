#include "request.h"

Req_prop *parseRequest(char *request)
{
  Req_prop *temp = (Req_prop *)malloc(sizeof(Req_prop));
  temp->request_line[0] = strtok(request, " ");
  for (size_t i = 1; i <= 2; i++)
  {
    temp->request_line[i] = strtok(request," ");
  }
}