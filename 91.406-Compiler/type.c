#include "type.h"
#include "utilities.h"
#include "main.h"
#include <stdio.h>

Type *make_type(int code)
{
  Type *type = (Type*)safe_malloc(sizeof(Type));
  type->code = code;
  type->is_array = FALSE;

  return type;
}

Interval *make_interval(int start, int end)
{
  Interval *interval = (Interval*)safe_malloc(sizeof(Interval));
  interval->start = start;
  interval->end = end;
  interval->next = NULL;

  return interval;
}
