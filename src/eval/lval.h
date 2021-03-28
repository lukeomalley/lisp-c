#include <stdio.h>
#include "../../lib/mpc.h"

#ifndef LVAL_H
#define LVAL_H

// Types of lval
enum
{
  LVAL_NUM,
  LVAL_ERR,
  LVAL_SYM,
  LVAL_SEXPR,
};

// Error types of lval
enum
{
  LERR_DIV_ZERO,
  LERR_BAD_OP,
  LERR_BAD_NUM,
};

typedef struct lval
{
  int type;
  long num;
  char *err;
  char *sym;

  /* Count of the lval pointers stored in a cell */
  int count;

  /* Pointer to pointers of lval */
  struct lval **cell;
} lval;

/* Constructor functions */
lval *lval_num(long x);
lval *lval_err(char *message);
lval *lval_sym(char *sym);
lval *lval_sexpr(void);

/* Convert ast into sexpr */
lval *lval_read(mpc_ast_t *t);

void lval_del(lval *v);
void lval_print(lval *v);
void lval_println(lval *v);

#endif