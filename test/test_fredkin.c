#include <stdio.h>
#include <stdlib.h>
#include "formats.h"
#include "grid.h"
#include "rules.h"
#include "typemods.h"

#define n_rules 5

int main ()
{
  uint k;
  cuz_dim_t i, j;
  struct cuz_err_t err, err2;
  struct cuz_grid gd, temp_gd;
  struct cuz_rule rules[n_rules];

  const uint n_iters = 15;
  const cuz_dim_t rows = 25, cols = 25;

  CUZ_INIT_ALL_RULES_FULL_RECT (
    rules, 
    cuz_fredkins_rule, 
    cuz_vneumann_interior,
    cuz_vneumann_periodic, 
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

  cuz_fill_gd (&gd, CUZ_OFF);

  for (j = 0; j < 5; j++)
    CUZ_PGRID_ELEM_AT (&gd, 12, j+12) = CUZ_ON;

  for (i = 0; i < 2; i++)
  {
    CUZ_PGRID_ELEM_AT (&gd, 13+i, 16) = CUZ_ON;
    CUZ_PGRID_ELEM_AT (&gd, 13+i, 14) = CUZ_ON;
  }

  cuz_printf_gd (&gd, &cuz_formats_xos);

  for (k = 1; k <= n_iters; k++)
  {
    puts ("-----------------------------------------------------------------");
    printf ("k = %u\n\n", k);
    cuz_step_gd (&gd, &temp_gd, rules, n_rules, 5, &err);
    cuz_printf_gd (&gd, &cuz_formats_xos);

    puts ("-----------------------------------------------------------------");

    if (err.code != CUZ_SUCCESS)
    {
      fprintf (stderr, "Failed step %u\n", k);
      fputs (err.msg, stderr);
    }
  }

  cuz_destroy_gd (&gd);
  cuz_destroy_gd (&temp_gd);
  puts ("Successfully recovered memory.");

  return err.code;
}
