#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./lval.h"
#include "../../lib/mpc.h"

/* Constructs a pointer to a new Number lval */
lval *lval_num(long x)
{
  lval *v = malloc(sizeof(lval));
  v->type = LVAL_NUM;
  v->num = x;
  return v;
}

/* Constructs a pointer to a new Error lval */
lval *lval_err(char *message)
{
  lval *v = malloc(sizeof(lval));
  v->type = LVAL_ERR;
  v->err = malloc(strlen(message) + 1);
  strcpy(v->err, message);
  return v;
}

/* Constructs a pointer to a new Symbol lval */
lval *lval_sym(char *sym)
{
  lval *v = malloc(sizeof(lval));
  v->type = LVAL_SYM;
  v->sym = malloc(strlen(sym) + 1);
  strcpy(v->sym, sym);
  return v;
}

/* Constructs a pointer to a new Sexpr lval */
lval *lval_sexpr(void)
{
  lval *v = malloc(sizeof(lval));
  v->type = LVAL_SEXPR;
  v->count = 0;
  v->cell = NULL;
  return v;
}

void lval_del(lval *v)
{
  switch (v->type)
  {
  case LVAL_NUM:
    break;

  case LVAL_ERR:
    /*  Free the string data */
    free(v->err);
    break;

  case LVAL_SYM:
    /*  Free the string data */
    free(v->sym);
    break;

  case LVAL_SEXPR:
    /*  Free all of the lvals inside the cell */
    for (int i = 0; i < v->count; i++)
    {
      lval_del(v->cell[i]);
    }

    /*  Free the memory allocated for the cell */
    free(v->cell);
    break;
  }

  /* Free the memory allocated for the lval itself */
  free(v);
}

lval *lval_read_num(mpc_ast_t *t)
{
  errno = 0;

  long x = strtol(t->contents, NULL, 10);
  return errno != ERANGE ? lval_num(x) : lval_err("invalid number");
}

/* Adds the x lval into the cell of the v lval */
lval *lval_add(lval *v, lval *x)
{
  v->count++;
  v->cell = realloc(v->cell, sizeof(lval *) * v->count);
  v->cell[v->count - 1] = x;
  return v;
}

lval *lval_read(mpc_ast_t *t)
{
  if (strstr(t->tag, "number"))
  {
    return lval_read_num(t);
  }

  if (strstr(t->tag, "symbol"))
  {
    return lval_sym(t->contents);
  }

  /* If 'root' or 'sexpr' create an empty list */
  lval *x = NULL;
  if (strcmp(t->tag, ">") == 0)
  {
    x = lval_sexpr();
  }
  if (strstr(t->tag, "sexpr") == 0)
  {
    x = lval_sexpr();
  }

  /* Fill this list with any valid expresion contained within */
  for (int i = 0; i < t->children_num; i++)
  {
    if (strcmp(t->children[i]->contents, "(") == 0)
    {
      continue;
    }

    if (strcmp(t->children[i]->contents, ")") == 0)
    {
      continue;
    }

    if (strcmp(t->children[i]->contents, "regex") == 0)
    {
      continue;
    }

    x = lval_add(x, lval_read(t->children[i]));
  }

  return x;
}

/* Forward declare function so it can be used within lval_print */
void lval_expr_print(lval *v, char open, char close);

/* Prints an lval */
void lval_print(lval *v)
{
  switch (v->type)
  {
  case LVAL_NUM:
    printf("%li", v->num);
    break;

  case LVAL_ERR:
    printf("Error: %s", v->err);
    break;

  case LVAL_SYM:
    printf("%s", v->sym);
    break;

  case LVAL_SEXPR:
    lval_expr_print(v, '(', ')');
    break;
  }
}

void lval_expr_print(lval *v, char open, char close)
{
  putchar(open);

  for (int i = 0; i < v->count; i++)
  {
    lval_print(v->cell[i]);

    if (i != (v->count - 1))
    {
      putchar(' ');
    }
  }

  putchar(close);
}

void lval_println(lval *v)
{
  lval_print(v);
  putchar('\n');
}