#include "../../lib/mpc.h"

mpc_parser_t *new_lispc_parser()
{
  mpc_parser_t *Number = mpc_new("number");
  mpc_parser_t *Symbol = mpc_new("symbol");
  mpc_parser_t *Sexpr = mpc_new("sexpr");
  mpc_parser_t *Expr = mpc_new("expr");
  mpc_parser_t *Lispc = mpc_new("lispc");

  mpca_lang(MPCA_LANG_DEFAULT,
            "                                          \
              number : /-?[0-9]+/ ;                    \
              symbol : '+' | '-' | '*' | '/' ;         \
              sexpr  : '(' <expr>* ')' ;               \
              expr   : <number> | <symbol> | <sexpr> ; \
              lispc : /^/ <expr>* /$/ ;               \
            ",
            Number, Symbol, Sexpr, Expr, Lispc);

  // mpc_cleanup(5, Number, Symbol, Sexpr, Expr, Lispc);

  return Lispc;
}
