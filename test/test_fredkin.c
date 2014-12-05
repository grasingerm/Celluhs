// Tests formatting
#include <stdio.h>
#include <stdlib.h>
#include "formats.h"
#include "grid.h"
#include "rules.h"
#include "typemods.h"

int main ()
{
  uint k;
  const uint n_iters = 15;
  const uint n_rules = 5;
  const cuz_dim_t rows = 25, cols = 25;
  cuz_dim_t i, j;

  struct cuz_err_t err;
  struct cuz_grid gd;
  
  struct cuz_rule rules[n_rules];

  rules[0].f = &cuz_fredkins;
  rules[0].get_nbr_states = &cuz_vneumann_interior;
  rules[0].range_i[0] = 1;
  rules[0].range_i[1] = 23;
  rules[0].range_j[0] = 1;
  rules[0].range_j[1] = 23;

  for (k = 1; k < n_rules; k++)
  {
    rules[k].f = &cuz_fredkins;
    rules[k].get_nbr_states = &cuz_vneumann_periodic;
  }

  rules[1].range_i[0] = 24;
  rules[1].range_i[1] = 24;
  rules[1].range_j[0] = 0;
  rules[1].range_j[1] = 24;

  rules[2].range_i[0] = 1;
  rules[2].range_i[1] = 23;
  rules[2].range_j[0] = 24;
  rules[2].range_j[1] = 24;

  rules[3].range_i[0] = 0;
  rules[3].range_i[1] = 0;
  rules[3].range_j[0] = 0;
  rules[3].range_j[1] = 24;

  rules[4].range_i[0] = 1;
  rules[4].range_i[1] = 23;
  rules[4].range_j[0] = 0;
  rules[4].range_j[1] = 0;

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
