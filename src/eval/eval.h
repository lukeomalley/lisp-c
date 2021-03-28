#include "../../lib/mpc.h"
#include "./lval.h"

#ifndef EVAL_H
#define EVAL_H

lval *eval_op(lval *x, char *op, lval *y);
lval *eval(mpc_ast_t *t);

#endif