#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "typemods.h"

int main ()
{
  ulonglong i, rows, cols;
  const uint seed = 30;
  const uint start = 2;
  const ulong end = 1000000000000;
  struct cuz_err_t err;
  struct grid gd;
  srand (seed);

  for (i = start; i <= end; i*=i)
  {
    rows = i;
    cols = rows;

    init_gd (&gd, rows, cols, &err);

    if (err.code == CUZ_SUCCESS)
      puts ("Grid successfully initialized.\n");
    else
    {
      puts ("Grid initialization failed.");
      puts (err.msg);
      printf ("Failed at size %llu by %llu\n", rows, cols);
      exit (err.code);
    }

    randomize_gd (&gd);
    // print_gd (&gd);
    printf ("Size %llu by %llu\n", rows, cols);
    destroy_gd (&gd);

    puts ("Successfully recovered memory.");
  }

  return 0;
}