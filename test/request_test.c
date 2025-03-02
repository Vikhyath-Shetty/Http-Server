#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
  char *request_line[3];
  char *headers[6];
} Req_prop;

Req_prop *parseRequest(char *request)
{
  Req_prop *temp = (Req_prop *)malloc(sizeof(Req_prop));
  temp->request_line[0] = strtok(request, " ");
  for (size_t i = 1; i <= 2; i++)
  {
    temp->request_line[i] = strtok(NULL, " ");
  }
  return temp;
}

int main()
{
  char request[] = "GET /api/contacts HTTP/1.0";
  Req_prop *request_prop = parseRequest(request);
  for (size_t i = 0; i < 3; i++)
  {
    printf("%s\n", request_prop->request_line[i]);
  }
  free(request_prop);
  return 0;
}