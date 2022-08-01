#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

void   error_print(char * fmt, ...);
void log_msg(char * fmt, ...);
size_t get_user_input(char * prompt, char ** buf_ptr);

#ifdef DEBUG
void   debug_print(char * fmt, ...);
#endif // DEBUG

#endif // UTILS_H