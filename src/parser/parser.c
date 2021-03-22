#include "../../lib/mpc.h"

mpc_parser_t *new_lispc_parser()
{

  mpc_parser_t *Number = mpc_new("number");
  mpc_parser_t *Operator = mpc_new("operator");
  mpc_parser_t *Expr = mpc_new("expr");
  mpc_parser_t *Lispc = mpc_new("lispc");

  // Define the grammar
  mpca_lang(MPCA_LANG_DEFAULT,
            "                                                     \
              number   : /-?[0-9]+/ ;                             \
              operator : '+' | '-' | '*' | '/' ;                  \
              expr     : <number> | '(' <operator> <expr>+ ')' ;  \
              lispc    : /^/ <operator> <expr>+ /$/ ;             \
            ",
            Number, Operator, Expr, Lispc);

  return Lispc;
}
