#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "formats.h"
#include "grid.h"
#include "rules.h"
#include "typemods.h"
#include <omp.h>

#define n_rules 5

int main (int argc, char* argv[])
{
  double start_time, end_time;
  uint k;
  char* rest;

  struct cuz_err_t err, err2;
  struct cuz_grid gd, temp_gd;
  struct cuz_rule rules[n_rules];
  
  uint n_iters = 100, seed = (uint) time (NULL);
  cuz_dim_t rows = 25, cols = 25;

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

  CUZ_INIT_ALL_RULES_FULL_RECT (
    rules, 
    cuz_conways_life, 
    cuz_moore_interior,
    cuz_moore_periodic, 
    rows,
    cols
    );

  cuz_init_gd (&gd, rows, cols, &err);
  cuz_init_gd (&temp_gd, rows, cols, &err2);

  if (err.code == CUZ_SUCCESS && err2.code == CUZ_SUCCESS)
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

  start_time = omp_get_wtime();
  for (k = 1; k <= n_iters; k++)
  {
    cuz_step_gd (&gd, &temp_gd, rules, n_rules, 5, &err);

    if (k % (n_iters / 20) == 0) printf("%u / %u iterations\n", k, n_iters);

    if (err.code != CUZ_SUCCESS)
    {
      fprintf (stderr, "Failed step %u\n", k);
      fputs (err.msg, stderr);
    }
  }

  end_time = omp_get_wtime();
  cuz_printf_gd (&gd, &cuz_formats_xos);
  printf("Time elapsed: %f\n", end_time - start_time);

  cuz_destroy_gd (&gd);
  cuz_destroy_gd (&temp_gd);
  puts ("Successfully recovered memory.");

  return err.code;
}
