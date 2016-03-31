#include "stack.h"
#include <stdlib.h>
#include "main.h"

Stack *make_stack()
{
  Stack* stack = malloc(sizeof(Stack));
  stack->items = malloc(sizeof(void*) * stack_default_length);
  stack->length = stack_default_length;
  stack->count = 0;

  return stack;
}

void* stack_peek(Stack *stack)
{
  return stack->items[stack->count - 1];
}

void* stack_pop(Stack *stack)
{
  stack->count--;
  return stack->items[stack->count];
}

void stack_push(Stack *stack, void *item)
{
  stack->items[stack->count] = item;
  stack->count = stack->count + 1;
}

int stack_is_empty(Stack *stack)
{
  if (stack->count == 0)
     return TRUE;
  else
    return FALSE;
}
