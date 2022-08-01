#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "client.h"
#include "server.h"

void   print_info(void);
size_t get_user_input(char * prompt, char ** buf_ptr);
void   main_loop(void);
void   print_help(void);


int main(void)
{
    print_info();

    main_loop();

    return 0;
}

void print_info(void)
{
    puts("####################\n"
         "  MESSENGER v0.1.0  \n"
         "####################\n");
}

void main_loop(void)
{
    char *    line_buf   = NULL;
    char *    first_word = NULL;
    size_t    chars_read;

    while((chars_read = get_user_input(">", &line_buf)) != (size_t)-1)
    {
        // Nothing was entered by the user
        if (chars_read == 1)
        {
            continue;
        }

        sscanf(line_buf, "%ms", &first_word);

        // Look for a command in the user input

        // EXIT 
        if (strcmp(first_word, "exit") == 0 ||
            strcmp(first_word, "quit") == 0 ||
            strcmp(first_word, "q")    == 0)
        {
            break;
        }

        // LISTEN
        if (strcmp(first_word, "listen") == 0 ||
            strcmp(first_word, "l")      == 0)
        {
            listen_command(line_buf);
            goto CLEAN_UP_MAIN;
        }

        // CONNECT
        if (strcmp(first_word, "connect") == 0 ||
            strcmp(first_word, "c"      ) == 0 )
        {
            connect_command(line_buf);
            goto CLEAN_UP_MAIN;
        }

        // If anything else, print help message
        print_help();

CLEAN_UP_MAIN:
        free(first_word);
        free(line_buf);
    }


    free(line_buf);
    free(first_word);
}

void print_help(void)
{
    puts("List of available commands:\n"
         "\t- l, listen: listen for a connection on a port at an ip address\n"
         "\t\tUsage: l, listen <ip address> <port>\n"
         "\t- c, connect: connect to an ip address at a given port\n"
         "\t\tUsage: c, connect <ip address> <port>\n"
         "\t- q, quit, exit: exit MESSENGER");
}

