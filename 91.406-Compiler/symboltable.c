#include "main.h"
#include "type.h"
#include "symbol.h"
#include <stdio.h>
#include "symboltable.h"
#include "utilities.h"

//Externals
extern int hash(char *text);

SymbolTable *make_symboltable()
{
  int i;

  SymbolTable *table = safe_malloc(sizeof(SymbolTable));
  table->parent = NULL;
  table->nested = -1;//Some invalid value

  for (i = 0; i < HASHSIZE; i++)
    {
      table->entries[i] = NULL;
    }

  return table;
}

void symboltable_delete(SymbolTable *table, Symbol *symbol)
{  
  Symbol *prev = NULL;
  Symbol *current;

  int h = hash(symbol->name);
  current = table->entries[h];

  while (current != NULL)
    {
      if (current != symbol)
	{
	  //Walk down the linked list
	  prev = current;
	  current = current->next;
	}
      else
	{
	  //Make the move
	  if (prev == NULL)
	    {
	      //If there is no previous symbol, we are at the start of the chain
	      table->entries[h] = table->entries[h]->next;
	    }
	  else
	    {
	      //Set previous to point to after this one
	      prev->next = current->next;
	    }
	  
	  symbol->next = NULL;
	  debug("Deleted %s from table at %d", symbol_to_string(symbol), h);
	  return;
	}
    }

	
  die("SymbolTable-Delete Symbol %s not found in table", symbol_to_string(symbol));
}

void symboltable_insert(SymbolTable *table, Symbol *s)
{
  //Check to see if it is already there, names are unique
  if (symboltable_lookup(table, s->name) != NULL)
    return;//die("Symbol already in table: %s", s->name);

  int h = hash(s->name);

  s->next = table->entries[h];
  table->entries[h] = s;

  debug("SymbolTable - Inserted %s into table at %d Symbol: %d Next: %d", s->name, h, s, s->next);
}

Symbol *symboltable_recurse(SymbolTable *table, char *text)
{
  SymbolTable *current = table;
  Symbol *found;
  while ((found = symboltable_lookup(current, text)) == NULL)
    {
      current = current->parent;
    }

  return found;
}

Symbol* symboltable_lookup(SymbolTable *table, char* text)
{
  int h = hash(text); 
  Symbol* symbol = table->entries[h];

  while (symbol != NULL)
    {
      if (symbol == symbol->next)
	die("SymbolTable::lookup - Infinite Loop");

      if (strcmp(symbol->name, text) == 0)
	break;
      else
	symbol = symbol->next;
    }

  return symbol;
}

void symboltable_dump(SymbolTable *table)
{
  int i;
  
  for (i = 0; i < HASHSIZE; i++)
    {
      Symbol *item = table->entries[i];
      while (item != NULL)
	{
	  //Print this item
	  printf("Current: %d Next: %d Hash %d Symbol %s Offset %d ", item, item->next,  i, item->name, item->offset);

	  if (item == item->next)
	    die("Infinite loop");
	  
	  if (item->type != NULL)
	    {
	      if (item->type->is_array == TRUE)
		{
		  printf(" Array C: %d ", item->type->c);
		  Interval *current = item->type->intervals;
		  while (current != NULL)
		    {
		      printf("[%d to %d], ", current->start, current->end);
		      
		      current = current->next;
		    }
		}

	      if (item->is_parameter == TRUE)
		printf(" PARAM");

	      printf(" Type: %d\n", item->type->code);

	      //Check to see if we point to another table
	      if ((item->symbols != NULL) && (item->type->code != TYPE_PROGRAM))//avoid infinite loop
		{
		  //if (item->parameters != NULL)
		  //  {
		  //    printf("Parameters: ");
		  //    Tac *current = item->parameters;

		  //    while ((current != NULL) && (current->op != 102))
		  //	{
		  //	  printf("%s, ", current->result->name);
		  //	  current = current->prev;
		  //	}
		  //   printf("\n");

		  //  }
		  
		  printf("\nDumping %s's Symbol Table at Nested: %d\n", item->name, item->symbols->nested);
		  symboltable_dump(item->symbols);
		  printf("Done\n\n");
		}
	    }
	  else
	    {
	      printf("\n");
	    }

	  //Now walk linked list
	  item = item->next;
	}
    }
}

//Stack functions
SymbolTable *symbol_stack_pop(Stack *stack)
{
  return (SymbolTable*)stack_pop(stack);
}

SymbolTable *symbol_stack_peek(Stack *stack)
{
  return (SymbolTable*)stack_peek(stack);
}

void symbol_stack_push(Stack *stack, SymbolTable *item)
{
  stack_push(stack, (void*)item);
}
