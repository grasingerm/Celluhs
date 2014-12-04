// Tests formatting
#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "typemods.h"
#include "formats.h"

int main ()
{
  // formatting functions to test
  void (*format_fs []) (cuz_state_t s, char* buffer) = {
    &cuz_formats_xos,
    &cuz_formats_xosb
  };
  char* f_descs [] = {
    "cuz_formats_xosb: Formats cell state to string of 'X's, ' 's, etc."
      " wrapped in spaces",
    "cuz_formats_xos: Formats cell state to string of 'X's, ' 's, etc."
      " wrapped in brackets"
  };

  const uint num_tests = 2;
  uint i;

  const cuz_dim_t rows = 15, cols = 15;
  const uint seed = 30;

  struct cuz_err_t err;
  struct cuz_grid gd;
  
  srand (seed);

  cuz_init_gd (&gd, rows, cols, &err);

  if (err.code == CUZ_SUCCESS)
    puts ("Grid successfully initialized.\n");
  else
  {
    puts ("Grid initialization failed.");
    puts (err.msg);
    printf ("Failed at size %lu by %lu\n", rows, cols);
    exit (err.code);
  }

  cuz_randomize_gd (&gd);
  cuz_print_gd (&gd);
  printf ("Size %lu by %lu\n\n", rows, cols);

  for (i = 0; i < num_tests; i++)
  {
    puts (f_descs [i]);
    cuz_printf_gd (&gd, format_fs [i]);
    puts("");
  }

  cuz_destroy_gd (&gd);
  puts ("Successfully recovered memory.");

  return 0;
}