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
void cuz_init_gd (struct cuz_grid* gd, const cuz_dim_t n_rows, 
  const cuz_dim_t n_cols, struct cuz_err_t* err)
{
  cuz_state_t* states = (cuz_state_t *) 
                          malloc ( (sizeof(cuz_state_t)) * n_rows * n_cols);
  CHECK_MEM_ALLOC (states, err, { return; });

  gd->states = states;
  gd->n_rows = n_rows;
  gd->n_cols = n_cols;

  err->code = CUZ_SUCCESS;
}

//! Grid destructor
//
// \param gd Pointer to grid to delete
void cuz_destroy_gd (struct cuz_grid* gd)
{
  free (gd->states);
}

//! Init grid to random states
//
// \param gd Pointer to grid to randomize
void cuz_randomize_gd (struct cuz_grid* gd)
{
  cuz_dim_t i, j;
  for (i = 0; i < gd->n_cols; i++)
    for (j = 0; j < gd->n_rows; j++)
      CUZ_PGRID_ELEM_AT (gd, i, j) = (rand () % 2 == 0) ? CUZ_ON : CUZ_OFF;
}

//! Fill grid to a default state
//
// \param gd Pointer to grid to fill
// \param s Default state
void cuz_fill_gd (struct cuz_grid* gd, const cuz_state_t s)
{
  cuz_dim_t i, j;
  for (i = 0; i < gd->n_cols; i++)
    for (j = 0; j < gd->n_rows; j++)
      CUZ_PGRID_ELEM_AT (gd, i, j) = s;
}

//! Fill grid to a default pattern
//
// \param gd Pointer to grid to fill
// \param ss Array of states
// \param ns Size of array of states
void cuz_fill_pat_gd (struct cuz_grid* gd, const cuz_state_t* ss, const uint ns)
{
  cuz_dim_t i, j;
  uint k;

  for (i = 0; i < gd->n_cols; i++)
    for (j = 0; j < gd->n_rows; j++)
    {
      CUZ_PGRID_ELEM_AT (gd, i, j) = ss [k];
      k++;
      if (k % ns == 0) k = 0;
    }
}

//! Display grid
//
// \param gd Pointer to grid to print
void cuz_print_gd (const struct cuz_grid* const gd)
{
  cuz_dim_t i, j;

  for (j = gd->n_rows; j > 0; j--)
  {
    for (i = 0; i < gd->n_cols; i++)
      printf (" %d ", CUZ_PGRID_ELEM_AT (gd, i, j-1));

    putchar ('\n');
  }
}

//! Display grid
//
// \param gd Pointer to grid to print
// \param stformat Pointer to state formatting function
void cuz_printf_gd (const struct cuz_grid* const gd, 
  void (*stformat) (cuz_state_t, char*))
{
  char _printf_cell_buffer [_CUZ_PRINTF_CELL_BUFFER_SZ];
  cuz_dim_t i, j;

  for (j = gd->n_rows; j > 0; j--)
  {
    for (i = 0; i < gd->n_cols; i++)
    {
      stformat (CUZ_PGRID_ELEM_AT (gd, i, j-1), _printf_cell_buffer);
      fputs (_printf_cell_buffer, stdout);
    }

    putchar ('\n');
  }
}

//! Simulate an iteration the grid
//
// \param gd Pointer to grid
// \param rules Array of rules
// \param n_rules Number of rules in array
// \param max_n_nbrs Maximum number of neighbors needed in rules
// \param err Pointer to cuz error type
void cuz_step_gd (struct cuz_grid* gd, struct cuz_rule* rules, 
  const uint n_rules, const uint max_n_nbrs, struct cuz_err_t* err)
{
  uchar alloc_flag = 0;
  cuz_state_t _nbr_states [_CUZ_NBR_BUFFER_SZ];
  cuz_state_t* c_nbr_states;
  c_nbr_states = _nbr_states; // default buffer

  if (max_n_nbrs > _CUZ_NBR_BUFFER_SZ)
  {
    c_nbr_states = (cuz_state_t *) malloc ( (sizeof(cuz_state_t))*max_n_nbrs );
    CHECK_MEM_ALLOC (c_nbr_states, err, { return; });
    alloc_flag = 1;
  }
  
  cuz_state_t* c_grid_states = (cuz_state_t *) malloc ( (sizeof(cuz_state_t)) * 
    gd->n_rows * gd->n_cols);
  CHECK_MEM_ALLOC (c_grid_states, err, {
    if (alloc_flag) free (c_nbr_states);
    return;
  });

  uint k, n_nbrs;
  cuz_dim_t i, j;
  struct cuz_rule* prule = rules;
  // TODO: vectorize
  // TODO: consider checking to make sure none of the neighborhoods exceed max
  for (k = 0; k < n_rules; k++)
  {
    for (i = prule->range_i[0]; i <= prule->range_i[1]; i++)
    {
      for (j = prule->range_j[0]; j <= prule->range_j[1]; j++)
      {
        n_nbrs = prule->get_nbr_states (c_nbr_states, gd, i, j);
        CUZ_ELEM_AT (c_grid_states, i, j, gd->n_rows) = 
          prule->f (c_nbr_states, n_nbrs);
      }
    }

    prule++;
  }

  if (alloc_flag) free (c_nbr_states);
  free (gd->states);
  gd->states = c_grid_states;

  return;
}
