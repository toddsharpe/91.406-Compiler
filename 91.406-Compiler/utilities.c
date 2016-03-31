#include "utilities.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "main.h"

//Externals
extern int debug_mode;

int hash(char *text)
{
  int first = (int)text[0];
  int hash = first % HASHSIZE;

  //return 1;
  return hash;
  //TODO make a real hash
}

void* safe_malloc(int n)
{
  void *p = malloc(n);

  if (p == NULL)
    {
      printf("malloc failed\n");
      exit(0);
    }

  return p;
}

void die(const char *format, ...)
{
  printf("Die: ");

  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);

  printf("\n");

  exit(0);
}

void debug(const char* format, ...)
{
  if (debug_mode == FALSE)
    return;

  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
  
  printf("\n");
}

//void debug(char *s)
//{
//  if (debug_mode == TRUE)
//    printf("%s\n", s);
//}

//void debug_string(char *s, char *string)
//{
//  if (debug_mode == TRUE)
//    printf("%s %s\n", s, string);
//
//}
