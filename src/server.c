#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <winsock2.h>

void error(char *message)
{
  fprintf(stderr, "%s:%d", message, WSAGetLastError());
  WSACleanup();
  exit(EXIT_FAILURE);
}

int start_server(uint16_t port)
{
 
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

  // Socket binding
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr("127.0.0.1");
  address.sin_port = htons(port);
  memset(&address.sin_zero, 0, 8);

  if (bind(server_socket, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR)
  {
    error("\nBinding failed");
  }

  // listening for request
  if (listen(server_socket, 5) == SOCKET_ERROR)
  {
    error("\nFailed to listen");
  }
  printf("\nListening to incoming request at %s", port);

  // accepting request
  SOCKET new_socket = accept(server_socket, NULL, NULL);
  if (new_socket == INVALID_SOCKET)
  {
    fprintf(stderr, "\nFailed to accept connection:%d", WSAGetLastError());
  }
  printf("\nAccepted a connection");

  // recieving request
  char request[1024] = {0};
  int bytes_recieved = recv(new_socket, request, sizeof(request) - 1, 0);
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

  if (send(new_socket, response, header_length + content_length, 0) == SOCKET_ERROR)
  {
    fprintf(stderr, "\nFailed to send response");
  }

  printf("\nResponse sent successfully");

  closesocket(new_socket);
  closesocket(server_socket);
  WSACleanup();

  return 0;
}