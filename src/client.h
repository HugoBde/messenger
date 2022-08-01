#ifndef CLIENT_H
#define CLIENT_H

#include <stdint.h>

int connect_to_server(int socket_fd, char * ip_addr, uint16_t port);

void connect_command(const char * command);

#endif //CLIENT_H