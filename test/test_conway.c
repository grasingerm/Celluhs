// Tests formatting
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "formats.h"
#include "grid.h"
#include "rules.h"
#include "typemods.h"

int main (int argc, char* argv[])
{
  uint k;
  uint n_iters = 100, seed = (uint) time (NULL);
  const uint n_rules = 5;
  cuz_dim_t rows = 25, cols = 25;
  char* rest;

  switch (argc)
  {
    case 5:
      seed = (uint) strtoul (argv [4], &rest, 10);
    case 4:
      rows = (cuz_dim_t) strtoul (argv [2], &rest, 10);
      cols = (cuz_dim_t) strtoul (argv [3], &rest, 10);
    case 2:
      n_iters = (uint) strtoul (argv [1], &rest, 10);
      break;
    case 1:
      break;
    default:
      printf ("usage: %s iterations [[rows, cols], [seed]]\n", argv [0]);
      exit (1);
  }

  printf ("%lu x %lu grid, %u iterations, seed = %u\n", 
    rows, cols, n_iters, seed);

  srand (seed);

  struct cuz_err_t err;
  struct cuz_grid gd;
  
  struct cuz_rule rules[n_rules];
  CUZ_INIT_ALL_RULES_FULL_RECT (
    rules, 
    cuz_conways_life, 
    cuz_moore_interior,
    cuz_moore_periodic, 
    rows,
    cols
    );

  cuz_init_gd (&gd, rows, cols, &err);

  if (err.code == CUZ_SUCCESS)
    puts ("Grid successfully initialized.\n");
  else
  {
    fputs ("Grid initialization failed.", stderr);
    fputs (err.msg, stderr);
    fprintf (stderr, "\nFailed at size %lu by %lu\n", rows, cols);
    exit (err.code);
  }

  cuz_randomize_gd (&gd);
  cuz_printf_gd (&gd, &cuz_formats_xos);

  for (k = 1; k <= n_iters; k++)
  {
    puts ("-----------------------------------------------------------------");
    printf ("k = %u\n\n", k);
    cuz_step_gd (&gd, rules, n_rules, 5, &err);
    cuz_printf_gd (&gd, &cuz_formats_xos);

    puts ("-----------------------------------------------------------------");

    if (err.code != CUZ_SUCCESS)
    {
      fprintf (stderr, "Failed step %u\n", k);
      fputs (err.msg, stderr);
    }
  }

  cuz_destroy_gd (&gd);
  puts ("Successfully recovered memory.");

  return err.code;
}
