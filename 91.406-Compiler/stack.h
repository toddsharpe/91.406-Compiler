#ifndef stack_h
#define stack_h

#include <stdlib.h>

#define stack_default_length 32

//Types
struct stack
{
  void** items;
  int count;
  int length;
};

typedef struct stack Stack;

//Prototypes
Stack *make_stack();
void* stack_peek(Stack* stack);
void* stack_pop(Stack* stack);
void stack_push(Stack* stack, void* item);
int stack_is_empty(Stack *stack);

#endif
