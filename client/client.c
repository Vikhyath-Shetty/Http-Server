#include <winsock2.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void error_exit(char *message, uint8_t cleanup)
{
  fprintf(stderr,"\n%s:%d", message, WSAGetLastError());
  if (cleanup)
    WSACleanup();
  exit(EXIT_FAILURE);
}

int main()
{
  // wsastartup
  WSADATA ws;
  if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
  {
    error_exit("Failed to initialize winsock", 0);
  }

  // create socket
  SOCKET client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (client_socket == INVALID_SOCKET)
  {
    error_exit("Failed to create a socket", 1);
  }

  // connecting to server
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(5000);
  address.sin_addr.s_addr = inet_addr("127.0.0.1");
  if (connect(client_socket, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR)
  {
    error_exit("Failed to connect to server", 1);
  }

  char buffer[1024];
  printf("Enter the message to send: ");
  gets(buffer);
  if (send(client_socket, buffer, strlen(buffer), 0) == SOCKET_ERROR)
  {
    error_exit("Failed to send request", 1);
  }
  
  ;
  int bytes_recieved = recv(client_socket,buffer,sizeof(buffer)-1,0);
  if(bytes_recieved == SOCKET_ERROR){
    error_exit("Failed to recieve response",1);
  }
  buffer[bytes_recieved] = '\0';
  printf("\n%s",buffer);

  closesocket(client_socket);
  WSACleanup();
  return 0;
}