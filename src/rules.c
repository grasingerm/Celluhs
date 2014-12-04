#include "grid.h"
#include "rules.h"

#define N_VNEUMANN(rank) (4*(rank)+1)

// cuz_state_t (*f) (cuz_state_t*, uint);
// void (*get_nbr_states) (cuz_state_t*, struct grid*, cuz_dim_t, cuz_dim_t, uint);

//! (Without checking for bounds) get vCUZ_CUZ_ON Neumann neighborhood of rank 1
//
// \param states Array in which to store vCUZ_CUZ_ON Neumann neighborhood
// \param gd Pointer to grid
// \param i Column of cell
// \param j Row of cell
// \return Number of neighbors in neighborhood
uint cuz_vneumann_interior (cuz_state_t* states, struct grid* gd, 
  cuz_dim_t i, cuz_dim_t j)
{
  *states = CUZ_PGRID_ELEM_AT(grid, i, j);
  *(states++) = CUZ_PGRID_ELEM_AT(grid, i+1, j);
  *(states++) = CUZ_PGRID_ELEM_AT(grid, i, j+1);
  *(states++) = CUZ_PGRID_ELEM_AT(grid, i-1, j);
  *(states++) = CUZ_PGRID_ELEM_AT(grid, i, j-1);

  return N_VNEUMANN(1);
}

//! Get vCUZ_CUZ_ON Neumann neighborhood of rank 1 using peroidicity at boundaries
//
// \param states Array in which to store vCUZ_CUZ_ON Neumann neighborhood
// \param gd Pointer to grid
// \param i Column of cell
// \param j Row of cell
// \return Number of neighbors in neighborhood
uint cuz_vneumann_periodic (cuz_state_t* states, struct grid* gd, 
  cuz_dim_t i, cuz_dim_t j)
{
  // heuristic: this implementatiCUZ_CUZ_ON assumes i and j will remain in bounds
  *states = CUZ_PGRID_ELEM_AT(grid, i, j);
  *(states++) = (i+1 < gd->n_cols) ? CUZ_PGRID_ELEM_AT (grid, i+1, j) : 
                                     CUZ_PGRID_ELEM_AT (grid, 0, j);
  *(states++) = (j+1 < gd->n_rows) ? CUZ_PGRID_ELEM_AT (grid, i, j+1) :
                                     CUZ_PGRID_ELEM_AT (grid, i, 0);
  *(states++) = (i > 0)   ? CUZ_PGRID_ELEM_AT (grid, i-1, j) :
                            CUZ_PGRID_ELEM_AT (grid, grid->n_cols-1, j);
  *(states++) = (j > 0)   ? CUZ_PGRID_ELEM_AT (grid, i, j-1) :
                            CUZ_PGRID_ELEM_AT (grid, i, grid->n_rows-1);

  return N_VNEUMANN(1);
}