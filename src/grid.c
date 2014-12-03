#include <stdlib.h>
#include <stdio.h>
#include "grid.h"

#define CHECK_MEM_ALLOC(palloc, pcuz_err, caller, ret_val_on_fail)  \
  if ( (palloc) == NULL )                                           \
  {                                                                 \
    (pcuz_err)->code = CUZ_MEMORY_ALLOC_ERR;                        \
    (pcuz_err)->msg = "Memory allocation error in '" caller "'"     \
    return ret_val;                                                 \
  }

//! Initialize cellular automata grid
//
// \param gd Pointer to grid to initialize
// \param n_rows Number of rows in grid
// \param n_cols Number of cols in grid
// \param err Pointer to cuz error type
void init_gd (struct grid* gd, uint n_rows, uint n_cols, struct cuz_err_t* err)
{
  uint* states = (uint *) malloc ( (sizeof(uint)) * n_rows * n_cols);
  CHECK_MEM_ALLOC (states, err, "init_gd", void);

  gd->states = states;
  gd->n_rows = n_rows;
  gd->n_cols = n_cols;

  err->code = CUZ_SUCCESS;
}

//! Grid destructor
//
// \param gd Pointer to grid to delete
void destroy_gd (struct grid* gd)
{
  free (gd->states);
}

//! Init grid to random states
//
// \param gd Pointer to grid to randomize
void randomize_gd (struct grid* gd)
{
  uint i, j;
  for (i = 0; i < gd->n_cols; i++)
    for (j = 0; j < gd->n_rows; j++)
      M_PGRID_ELEM_AT (gd, i, j) = (rand () % 2 == 0) ? ON : OFF;
}

//! Display grid
//
// \param gd Pointer to grid to print
void print_gd (struct grid* gd)
{
  uint i;
  int j;

  for (j = gd->n_rows-1; j >= 0; j--)
  {
    for (i = 0; i < gd->n_cols; i++)
      printf ("%d ", M_PGRID_ELEM_AT (gd, i, j));

    putchar ('\n');
  }
}

void step (struct grid* gd, void (*rule) (uint i, uint j), 
  struct cuz_err_t* err)
{
  uint i, j;
  uint* states = (uint *) malloc ( (sizeof(uint)) * n_rows * n_cols);
  CHECK_MEM_ALLOC (states, err, "step", void);

  i = 1;
  j = i;

  return;
}