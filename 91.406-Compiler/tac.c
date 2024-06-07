#include "tac.h"
#include "symbol.h"
#include "main.h"
#include <stdio.h>
#include "utilities.h"
#include <stdarg.h>

Tac *make_tac(int op, Symbol *result, Symbol *operand1, Symbol *operand2)
{
  Tac* tac = (Tac*)safe_malloc(sizeof(Tac));
  tac->next = NULL;
  tac->prev = NULL;

  tac->op = op;
  tac->result = result;
  tac->operand1 = operand1;
  tac->operand2 = operand2;

  tac->location = NULL;
  tac->condition = NULL;
  
  //debug("Make_Tac: Op: %d Result: %s Operand1: %s Operand2: %s", op, symbol_to_string(result), symbol_to_string(operand1), symbol_to_string(operand2));

  return tac;
}

Tac *last_tac(Tac *first)
{
  while (first->prev != NULL)
    first = first->prev;

  return first;
}

Tac *make_label_tac(int op, Tac *location, Symbol *condition)
{
  Tac *tac = (Tac*)safe_malloc(sizeof(Tac));
  tac->next = NULL;
  tac->prev = NULL;

  tac->op = op;
  
  tac->location = location;
  tac->condition = condition;
  
  //debug("Make_Label_Tac Op: %d Location: %d Condition: %d", op, location, symbol_to_string(condition));

  return tac;
}

//Input - the first tac in a backwards linked list
//Output - last in a forwards linked list
Tac *reverse_tac(Tac *first)
{
  Tac *current = first;
  Tac *next = NULL;

  while (current->prev != NULL)
    {
      //Get next element
      next = current->prev;

      //Wire forward pointer
      next->next = current;

      //Now loop
      current = next;

    }

  return next;
}

//If either tac is null, we return the other one
//Get the last tac in second
//point the previos field to the first

//hence the code in first is put before the code in second
Tac *join_tac(Tac *first, Tac *second)
{
  Tac *current;
  
  if (first == NULL)
    return second;

  if (second == NULL)
    return first;

  current = second;
  while (current->prev != NULL)
    {
      if (current == current->prev)
	die("Self-Pointing Tac: %d", current->prev);

      current = current->prev;
    }

  if (current->prev != NULL)
    die("Tac::join_tac Current->Prev: %d", current->prev);

  current->prev = first;

  return second;
}

//NOTE: Broken :(
//this function joins tacs back to front
//Typical usage: (4, $1, $3, $4, $5)
//The first arg becomes the prev, and current becomes the second. We move down the list to the last Tac in current, called end, and use end->prev to be first
//Rinse repeat, return current
//if there is a null tac, we ignore it
Tac *join_tacs(int num, ...)
{
  Tac *current = NULL;//This points to
  Tac *end;//
  Tac *prev;

  //Prepare arguments
  va_list args;
  va_start(args, num);

  //Get out first argument, which will be the caboose (sp?)
  //Make sure to get the first that isn't null
  do
  {
    prev = va_arg(args, Tac*);
    num--;
    if (num <= 0)
      die("Join Tac - All tacs were Null");

  } while (prev == NULL);

  for (; num > 0; num--)
    {
      
      //Get our first non-null next term
      do
	{
	  current = va_arg(args, Tac*);
	  num--;
	  if (num <= 0)
	    goto clean_and_return;
	} while (current == NULL);

      end = current;//Assume the end of this Tac list is the start
      while (end->prev != NULL)
	end = end->prev;//navigate through the list

      //Now we have the last element in this tac
      end->prev = prev;

    
    } 

 clean_and_return:
  va_end(args);

  return current;
}

void tac_dump(Tac *tac)
{
  if (tac == NULL)
    return;//Nothing to do here

  int reverse = tac->prev != NULL;

  Tac *current = tac;

  while (current != NULL)
    {
      printf("Current %p Op: %d ", current, current->op);

      //if (current->op == TAC_CALL)
      //	printf("Location: %d Return: %s\n", current->location, symbol_to_string(current->condition));
      if ((current->op == TAC_GOTO) || (current->op == TAC_IFZ) || (current->op == TAC_IFNZ))
	printf("Location: %p Condition: %s\n", current->location, symbol_to_string(current->condition));
      else
	printf("Result: %s (%p) Operand1: %s Operand2: %s\n", symbol_to_string(current->result), current->result, symbol_to_string(current->operand1), symbol_to_string(current->operand2));

      if (reverse)
	current = current->prev;
      else
	current = current->next;
    }
}
