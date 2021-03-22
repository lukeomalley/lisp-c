#include "../../lib/mpc.h"
#include "./eval.h"
#include "./lval.h"

lval eval_op(lval x, char *op, lval y)
{
  if (strcmp(op, "+") == 0)
  {
    return lval_num(x.num + y.num);
  }
  else if (strcmp(op, "-") == 0)
  {
    return lval_num(x.num - y.num);
  }
  else if (strcmp(op, "*") == 0)
  {
    return lval_num(x.num * y.num);
  }
  else if (strcmp(op, "/") == 0)
  {
    return y.num == 0 ? lval_err(LERR_DIV_ZERO) : lval_num(x.num / y.num);
  }
  else
  {
    return lval_err(LERR_BAD_OP);
  }
}

lval eval(mpc_ast_t *t)
{
  // If tagged as number return it
  if (strstr(t->tag, "number"))
  {
    errno = 0;
    long x = strtol(t->contents, NULL, 10);
    return errno != ERANGE ? lval_num(x) : lval_err(LERR_BAD_NUM);
  }

  char *op = t->children[1]->contents;

  lval x = eval(t->children[2]);

  int i = 3;
  while (strstr(t->children[i]->tag, "expr"))
  {
    x = eval_op(x, op, eval(t->children[i]));
    i++;
  }

  return x;
}