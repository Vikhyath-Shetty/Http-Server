#ifndef SOCKET_H
#define SOCKET_H

#include <winsock2.h>
#include <stdint.h>

SOCKET init_socket(uint16_t port);

#endif