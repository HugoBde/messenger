#include "utils.h"

#include <stdarg.h>
#include <stdio.h>

void error_print(char * fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fputs("[\x1b[31mERROR\x1b[0m] ", stdout);
    vprintf(fmt, args);
    va_end(args);
}

void log_msg(char * fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fputs("[\x1b[32mLOG\x1b[0m] ", stdout);
    vprintf(fmt, args);
    va_end(args);
}

size_t get_user_input(char * prompt, char ** buf_ptr)
{
    *buf_ptr = NULL;
    size_t buf_size;
    printf("%s ", prompt);
    return getline(buf_ptr, &buf_size, stdin);
}

#ifdef DEBUG
void debug_print(char * fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fputs("[\x1b[33mDEBUG\x1b[0m] ", stdout);
    vprintf(fmt, args);
    va_end(args);
}
#endif // DEBUG