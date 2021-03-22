#include <stdio.h>

#ifndef LVAL_H
#define LVAL_H

// Types of lval
enum
{
  LVAL_NUM,
  LVAL_ERR
};

// Error types
enum
{
  LERR_DIV_ZERO,
  LERR_BAD_OP,
  LERR_BAD_NUM
};

typedef struct
{
  int type;
  long num;
  int err;
} lval;

lval lval_num(long x);
lval lval_err(long x);
void lval_print(lval v);
void lval_println(lval v);

#endif