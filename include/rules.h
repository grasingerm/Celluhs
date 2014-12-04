#ifndef __RULES_H__
#define __RULES_H__

#include "grid.h"

// state_t (*f) (state_t*, uint);
// void (*get_nbr_states) (state_t*, struct grid*, dim_t, dim_t, uint);

void moore_interior (state_t* states, struct grid* gd, dim_t i, dim_t j,
  uint n_nbrs)
{
  *states = CUZ_PGRID_ELEM_AT(grid, i, j);
  *(states++) = CUZ_PGRID_ELEM_AT(grid, i+1, j);
  *(states++) = CUZ_PGRID_ELEM_AT(grid, i, j+1);
  *(states++) = CUZ_PGRID_ELEM_AT(grid, i-1, j);
  *(states++) = CUZ_PGRID_ELEM_AT(grid, i, j-1);
}

void moore_periodic (state_t* states, struct grid* gd, dim_t i, dim_t j,
  uint n_nbrs)
{
  *states = CUZ_PGRID_ELEM_AT(grid, i, j);
  *(states++) = CUZ_PGRID_ELEM_AT(grid, i+1, j);
  *(states++) = CUZ_PGRID_ELEM_AT(grid, i, j+1);
  *(states++) = CUZ_PGRID_ELEM_AT(grid, i-1, j);
  *(states++) = CUZ_PGRID_ELEM_AT(grid, i, j-1);
}

#endif