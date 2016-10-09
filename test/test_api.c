// Tests formatting
#include "formats.h"
#include "grid.h"
#include "typemods.h"
#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  const char *data_fname = "fredkins_init-f.json";

  json_t *root;
  json_error_t error;

  root = json_load_file(data_fname, size_t flags, &error);

  return 0;
}
