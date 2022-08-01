#include "server.h"

#include <stdint.h>
#include <stdio.h>

#include "utils.h"

void listen_command(const char * command)
{
    char     ip_address[16];
    uint16_t port;

    if (sscanf(command, "%*s %15s %hd", ip_address, &port) != 2)
    {
        error_print("Invalid command syntax\n"
                    "Usage: > listen <IP ADDRESS> <PORT>\n");
    }
}