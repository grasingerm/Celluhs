#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "typemods.h"

int main ()
{
  const uint seed = 30;
  const uint rows = 6;
  const uint cols = 6;
  struct cuz_err_t err;
  struct grid gd;

  init_gd (&gd, rows, cols, &err);

  if (err.code == CUZ_SUCCESS)
    puts ("Grid successfully initialized.\n");
  else
  {
    puts ("Grid initialization failed.");
    puts (err.msg);
    exit (err.code);
  }

  srand (seed);
  randomize_gd (&gd);
  print_gd (&gd);

  destroy_gd (&gd);
  puts ("successfully recovered memory.");

  return 0;
}