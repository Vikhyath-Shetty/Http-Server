#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "socket.h"

int start_server(uint16_t port)
{
  SOCKET server_socket = init_socket(port);
  printf("\nServer is listening to port: %d", port);

  uint8_t connection = 1;
  while (1)
  {
    SOCKET client_socket = accept(server_socket, NULL, NULL);
    if (client_socket == SOCKET_ERROR)
    {
      fprintf(stderr, "Failed to connect to client-%d", connection++);
      continue;
    }
    printf("\nConnected to client-%d", connection);

    if (connection > 5)
      connection = 1;

    char request[1024] = {0};
    int bytes_recieved = recv(client_socket, request, sizeof(request) - 1, 0);
    if (bytes_recieved == SOCKET_ERROR)
    {
      fprintf(stderr, "\nFailed to recieve request from client-%d", connection++);
      closesocket(client_socket);
      continue;
    }
    request[bytes_recieved] = '\0';
    printf("\nRequest from client-%d is : %s",connection, request);

    const char *html_content = "<html><body><h1>Hello Client!</h1></body></html>";
    int content_length = strlen(html_content);

    char response[2048];
    int header_length = snprintf(
        response, sizeof(response),
        "HTTP/1.0 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %d\r\n\r\n",
        content_length);
      
    // strcat(response, html_content);
    memcpy(response+header_length,html_content,content_length);

    if (send(client_socket, response, header_length + content_length, 0) == SOCKET_ERROR)
    {
      fprintf(stderr, "\nFailed to send response to client-%d", connection++);
      closesocket(client_socket);
      continue;
    }
    printf("\nResponse sent successfully to client-%d", connection);
    connection++;
  }

  close_server(server_socket);
  return 0;
}