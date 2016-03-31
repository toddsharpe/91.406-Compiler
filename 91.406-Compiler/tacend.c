#include "tacend.h"
#include "symbol.h"
#include "expression.h"
#include "utilities.h"
#include "main.h"
#include "tac.h"
#include <stdlib.h>
#include <stdio.h>
#include "type.h"
#include "frontend.h"

Tac *tac_assign(Symbol *symbol, Expression *expression)
{
  debug("TAC-Assign %s to %s Type: %d", symbol_to_string(symbol), symbol_to_string(expression->result), symbol->type->code);

  Tac *code;

  //debug("TAC-Assign: %s TYPE: %d to %s TYPE: %d", symbol->name, symbol->type->code, expression->result->name, expression->result->type->code);

  //if (symbol->type->is_variable != TRUE)
  //  die("Symbol isn't a variable");
  
  //if ((symbol->type->code == TYPE_INTEGER) && (expression->result->type->code == TYPE_NATURAL))
  //  goto do_tac;

  //if (symbol->type->code == expression->result->type->code)
  //  goto do_tac;

  //goto do_tac;//We'll check types...never....
  //die("Symbol isn't same type as expression");
 
 do_tac: 
  code = make_tac(TAC_COPY, symbol, expression->result, NULL);
  code->prev = expression->tac;

  free(expression);

  return code;
}

//Assembly if sandwich
//IFZ - GOTO Else label
// True tacs
//Goto end tac

//Expression tac
//If Z
//True tac
//Goto ->end
//False label tac
//False tac
//End Tac
Tac *tac_if_else(Expression *condition, Tac *true, Tac *false)
{
  Tac *false_tac = make_tac(TAC_LABEL, make_label(), NULL, NULL);
  Tac *end_tac = make_tac(TAC_LABEL, make_label(), NULL, NULL);

  Tac *if_tac = make_label_tac(TAC_IFZ, false_tac, condition->result);
  Tac *goto_tac = make_label_tac(TAC_GOTO, end_tac, NULL);

  if_tac->prev = condition->tac;//We need to execute the condition before making the decision
  goto_tac->prev = join_tac(if_tac, true);//Put the if tac before the true tac and put them all before the goto tac

  false_tac->prev = goto_tac;//Before false tac, we have the goto tac
  end_tac->prev = join_tac(false_tac, false);

  return end_tac;
}

Tac *tac_if(Expression *condition, Tac *true)
{
  Tac *end_tac = make_tac(TAC_LABEL, make_label(), NULL, NULL);
  Tac *if_tac = make_label_tac(TAC_IFZ, end_tac, condition->result);

  if_tac->prev = condition->tac;//We need to execute condition before making decision
  end_tac->prev = join_tac(if_tac, true);//Put the if tac before the true tac

  //Give back
  free(condition);

  return end_tac;//Return the end of the statement
}

Tac *tac_while(Expression *condition, Tac *body)
{
  Tac *end_tac = make_tac(TAC_LABEL, make_label(), NULL, NULL);
  Tac *goto_tac = make_label_tac(TAC_GOTO, end_tac, NULL);

  goto_tac->prev = body;

  return join_tac(end_tac, tac_if(condition, goto_tac));
}

//When the subprogram_head reduces, this is called
Tac *tac_procedure_start(Symbol *function, Tac *arguments)
{
  Tac *begin_label;
  Tac *code;

  //begin_label = make_label_tac(TAC_BEGINFUNCTION, null, NULL);
  begin_label = make_tac(TAC_BEGINFUNCTION, function, NULL, NULL);

  code = join_tac(begin_label, arguments);

  return code;
}
