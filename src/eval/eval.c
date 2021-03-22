#include "../../lib/mpc.h"

long eval_op(long x, char *op, long y)
{
  if (strcmp(op, "+") == 0)
  {
    return x + y;
  }
  else if (strcmp(op, "-") == 0)
  {
    return x - y;
  }
  else if (strcmp(op, "*") == 0)
  {
    return x * y;
  }
  else if (strcmp(op, "/") == 0)
  {
    return x / y;
  }
  else
  {
    return 0;
  }
}

long eval(mpc_ast_t *t)
{
  // If tagged as number return it
  if (strstr(t->tag, "number"))
  {
    return atoi(t->contents);
  }

  char *op = t->children[1]->contents;

  long x = eval(t->children[2]);

  int i = 3;
  while (strstr(t->children[i]->tag, "expr"))
  {
    x = eval_op(x, op, eval(t->children[i]));
    i++;
  }

  return x;
}