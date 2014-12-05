// Tests formatting
#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "typemods.h"
#include "formats.h"

int main ()
{
  const char* data_fname = "fredkins_init-f.json";

  json_t *root;
  json_error_t error;

  root = json_load_file (data_fname, size_t flags, &error);


  return 0;
}