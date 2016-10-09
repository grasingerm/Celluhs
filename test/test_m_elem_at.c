#include "grid.h"
#include "typemods.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  cuz_dim_t i, rows, cols;
  const uint seed = 30;
  const cuz_dim_t start = 2;
  const cuz_dim_t end = 1000000000000;
  struct cuz_err_t err;
  struct cuz_grid gd;
  srand(seed);

  for (i = start; i <= end; i *= i) {
    rows = i;
    cols = rows;

    cuz_init_gd(&gd, rows, cols, &err);

    if (err.code == CUZ_SUCCESS)
      puts("Grid successfully initialized.\n");
    else {
      puts("Grid initialization failed.");
      puts(err.msg);
      printf("Failed at size %lu by %lu\n", rows, cols);
      exit(err.code);
    }

    cuz_randomize_gd(&gd);
    cuz_print_gd(&gd);
    printf("Size %lu by %lu\n", rows, cols);
    cuz_destroy_gd(&gd);

    puts("Successfully recovered memory.");
  }

  return 0;
}
