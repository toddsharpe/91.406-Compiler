#ifndef utilities_h
#define utilities_h

#include <stdarg.h>

void* safe_malloc(int size);
void die(const char* format, ...);
int hash(char *text);

//Debug output
void debug(const char* format, ...);

//void debug(char *text);
//void debug_string(char *text, char *string);

#endif
