#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <stdlib.h>
#include "socket.h"




int start_server(uint16_t port)
{

  SOCKET server_socket = init_socket(port);
  if(server_socket == SOCKET_ERROR || server_socket == INVALID_SOCKET){
    return EXIT_FAILURE;
  }
  printf("\nServer is listening to port: %d",port);






  

  // accepting connection
  SOCKET client_socket = accept(server_socket, NULL, NULL);
  if (client_socket == INVALID_SOCKET)
  {
    fprintf(stderr, "\nFailed to accept connection:%d", WSAGetLastError());
  }
  printf("\nAccepted a connection");

  // recieving request
  char request[1024] = {0};
  int bytes_recieved = recv(client_socket, request, sizeof(request) - 1, 0);
  if (bytes_recieved == SOCKET_ERROR)
  {
    fprintf(stderr, "\nFailed to recieve request from client");
  }
  request[bytes_recieved] = '\0';
  printf("\nRequest is : %s", request);

  // sending response
  const char *html_content = "<html><body><h1>Hello Client!</h1></body></html>";
  int content_length = strlen(html_content);

  char response[2048];
  int header_length = snprintf(
      response, sizeof(response),
      "HTTP/1.0 200 OK\r\n"
      "Content-Type: text/html\r\n"
      "Content-Length: %d\r\n\r\n",
      content_length);

  strcat(response, html_content);

  if (send(client_socket, response, header_length + content_length, 0) == SOCKET_ERROR)
  {
    fprintf(stderr, "\nFailed to send response");
  }

  printf("\nResponse sent successfully");

  close_server(client_socket, server_socket);
  return 0;
}