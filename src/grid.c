#include <stdlib.h>
#include <stdio.h>
#include "grid.h"
#include "debug.h"

//! Initialize cellular automata grid
//
// \param gd Pointer to grid to initialize
// \param n_rows Number of rows in grid
// \param n_cols Number of cols in grid
// \param err Pointer to cuz error type
void init_gd (struct grid* gd, dim_t n_rows, dim_t n_cols, 
  struct cuz_err_t* err)
{
  state_t* states = (state_t *) malloc ( (sizeof(state_t)) * n_rows * n_cols);
  CHECK_MEM_ALLOC (states, err, );

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
  ulonglong i, j;
  for (i = 0; i < gd->n_cols; i++)
    for (j = 0; j < gd->n_rows; j++)
      CUZ_PGRID_ELEM_AT (gd, i, j) = (rand () % 2 == 0) ? ON : OFF;
}

//! Display grid
//
// \param gd Pointer to grid to print
void print_gd (struct grid* gd)
{
  ulonglong i, j;

  for (j = gd->n_rows; j > 0; j--)
  {
    for (i = 0; i < gd->n_cols; i++)
      printf ("%d ", CUZ_PGRID_ELEM_AT (gd, i, j-1));

    putchar ('\n');
  }
}

//! Simulate an iteration on the grid
void step (struct grid* gd, struct rule* rules, uint n_rules, uint n_nbrs,
  struct cuz_err_t* err)
{
  uchar alloc_flag = 0;
  state_t _nbr_states [_CUZ_NBR_BUFFER_SZ];
  state_t* c_nbr_states;
  c_nbr_states = _nbr_states; // default buffer

  if (n_nbrs > _CUZ_NBR_BUFFER_SZ)
  {
    c_nbr_states = (state_t *) malloc ( (sizeof(state_t))*n_nbrs );
    CHECK_MEM_ALLOC (c_temp_states, err, );
    alloc_flag = 1;
  }
  
  state_t* c_grid_states = (state_t *) malloc ( (sizeof(state_t)) * 
    gd->n_rows * gd->n_cols);
  CHECK_MEM_ALLOC (states, err, 
    ((alloc_flag) ? free (c_temp_states) : _ret_void ()));

  uint k;
  dim_t i,j;
  struct rule* prule;
  // TODO: vectorize
  for (k = 0; k < n_rules; k++)
  {
    for (i = prule->range_i[0]; i <= prule->range_i[1]; i++)
    {
      for (j = prule->range_j[0]; j <= prule->range_j[1]; j++)
      {
        prule->get_nbr_states (c_nbr_states, gd, i, j, n_nbrs);
        CUZ_ELEM_AT (c_grid_states, i, j, gd->n_rows) = 
          prule->f (c_nbr_states, n_nbrs);
      }
    }

    prule++;
  }

  if (alloc_flag) free (c_temp_states);
  free (gd->states);
  gd->states = c_grid_states;

  return;
}