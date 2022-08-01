#include "client.h"

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <sys/socket.h>

#include "utils.h"

int connect_to_server(int socket_fd, char * ip_addr, uint16_t port)
{
    struct sockaddr_in target_addr;

    target_addr.sin_family = AF_INET;
    target_addr.sin_port   = htons(port);

    if(inet_aton(ip_addr, &target_addr.sin_addr) < 0)
    {
        error_print("%s is not a valid IP address\n", ip_addr);
        return -1;
    }

    if(connect(socket_fd,
       (struct sockaddr *)&target_addr,
       sizeof(target_addr)) == -1)
    {
        error_print("Failed to connect to %s:%d\n", ip_addr, port);
        return -1;
    }

    return 0;
}

void connect_command(const char * command)
{
    char     ip_addr[16];
    uint16_t port;

    // Get parameters from the input command
    if (sscanf(command, "%*s %15s %hd", ip_addr, &port) != 2)
    {
        error_print("Invalid command syntax\n"
                    "Usage: > connect <IP ADDRESS> <PORT>\n");
        return;
    }

    // Get a socket from the OS
    int socket_fd;
    if ((socket_fd  = socket(AF_INET, SOCK_STREAM, 0))== -1)
    {
        error_print("Failed to get socket\n");
        return;
    }

    // Connect port
    if (connect_to_server(socket_fd, ip_addr, port) == -1)
    {
        goto CLEAN_UP_CONNECT_COMMAND;
    }

    log_msg("Successfully connected to %s:%d\n", ip_addr, port);

    size_t chars_read;
    char * line_buf;

    while((chars_read = get_user_input(">", &line_buf)) != (size_t)-1)
    {
        if (chars_read == 1)
        {
            break;
        }

        // User attempted to use a command
        if (line_buf[0] == '/')
        {

        }
        send(socket_fd, line_buf, chars_read, 0);
    }

    log_msg("Disconnecting...\n");

CLEAN_UP_CONNECT_COMMAND:
    close(socket_fd);
}