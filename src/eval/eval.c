#include "../../lib/mpc.h"
#include "./eval.h"
#include "./lval.h"

lval *eval_op(lval *x, char *op, lval *y)
{
  if (strcmp(op, "+") == 0)
  {
    return lval_num(x->num + y->num);
  }
  else if (strcmp(op, "-") == 0)
  {
    return lval_num(x->num - y->num);
  }
  else if (strcmp(op, "*") == 0)
  {
    return lval_num(x->num * y->num);
  }
  else if (strcmp(op, "/") == 0)
  {
    return y->num == 0 ? lval_err("divide by zero") : lval_num(x->num / y->num);
  }
  else
  {
    return lval_err("unknown opeartor");
  }
}

lval *eval(mpc_ast_t *t)
{
  // If tagged as number return it
  if (strstr(t->tag, "number"))
  {
    errno = 0;
    long x = strtol(t->contents, NULL, 10);
    return errno != ERANGE ? lval_num(x) : lval_err("invalid number");
  }

  char *op = t->children[1]->contents;

  lval *x = eval(t->children[2]);

  int i = 3;
  while (strstr(t->children[i]->tag, "expr"))
  {
    x = eval_op(x, op, eval(t->children[i]));
    i++;
  }

  return x;
}