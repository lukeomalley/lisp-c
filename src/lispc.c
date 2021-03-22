#include <stdio.h>
#include <stdlib.h>
#include "../lib/mpc.h"
#include "./eval/eval.h"

#ifdef _WIN32
#include <string.h>

// Declare a buffer for user input of size 2048. Static makes variable local to this file
static char buffer[2048];

// Fake readline function
char *readline(char *prompt)
{
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char *cpy = malloc(strlen(buffer) + 1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy) - 1] = '\0';
  return cpy;
}

// fake add_history function
void add_history(char *unused) {}

#else
#include <editline/readline.h>
#endif

int main(int argc, char **argv)
{
  // Create parsers
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

  puts("Lisp C Version 0.0.1");
  puts("Press Ctrl+c to Exit\n");

  while (1)
  {
    char *input = readline("lispc > ");

    add_history(input);

    // Attempt to parsee the user input
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispc, &r))
    {
      long result = eval(r.output);
      printf("%li\n", result);
      mpc_ast_delete(r.output);
    }
    else
    {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free(input);
  }

  return 0;
}