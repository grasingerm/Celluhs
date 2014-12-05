#include "grid.h"
#include "rules.h"

#define N_VNEUMANN(rank) (4*(rank)+1)

// cuz_state_t (*f) (cuz_state_t*, uint);
// void (*get_nbr_states) (cuz_state_t*, struct grid*, cuz_dim_t, cuz_dim_t, uint);

//! (Without checking for bounds) get von Neumann neighborhood of rank 1
//
// \param states Array in which to store von Neumann neighborhood
// \param gd Pointer to grid
// \param i Column of cell
// \param j Row of cell
// \return Number of neighbors in neighborhood
uint cuz_vneumann_interior (cuz_state_t* states, struct cuz_grid* gd, 
  cuz_dim_t i, cuz_dim_t j)
{
  *states = CUZ_PGRID_ELEM_AT(gd, i, j);
  *(states++) = CUZ_PGRID_ELEM_AT(gd, i+1, j);
  *(states++) = CUZ_PGRID_ELEM_AT(gd, i, j+1);
  *(states++) = CUZ_PGRID_ELEM_AT(gd, i-1, j);
  *(states++) = CUZ_PGRID_ELEM_AT(gd, i, j-1);

  return N_VNEUMANN(1);
}

//! Get vCUZ_CUZ_ON Neumann neighborhood of rank 1 using peroidicity at boundaries
//
// \param states Array in which to store von Neumann neighborhood
// \param gd Pointer to grid
// \param i Column of cell
// \param j Row of cell
// \return Number of neighbors in neighborhood
uint cuz_vneumann_periodic (cuz_state_t* states, struct cuz_grid* gd, 
  cuz_dim_t i, cuz_dim_t j)
{
  // heuristic: this implementation assumes i and j will remain in bounds
  *states = CUZ_PGRID_ELEM_AT(gd, i, j);
  *(states++) = (i+1 < gd->n_cols) ? CUZ_PGRID_ELEM_AT (gd, i+1, j) : 
                                     CUZ_PGRID_ELEM_AT (gd, 0, j);
  *(states++) = (j+1 < gd->n_rows) ? CUZ_PGRID_ELEM_AT (gd, i, j+1) :
                                     CUZ_PGRID_ELEM_AT (gd, i, 0);
  *(states++) = (i > 0)   ? CUZ_PGRID_ELEM_AT (gd, i-1, j) :
                            CUZ_PGRID_ELEM_AT (gd, gd->n_cols-1, j);
  *(states++) = (j > 0)   ? CUZ_PGRID_ELEM_AT (gd, i, j-1) :
                            CUZ_PGRID_ELEM_AT (gd, i, gd->n_rows-1);

  return N_VNEUMANN(1);
}

//! Update state based on fredkin's rule
//
// \param states Array of neighbor states
// \param n_nbrs Number of neighbors in neighborhood
// \return Next state
cuz_state_t cuz_fredkins_rule (cuz_state_t* states, uint n_nbrs)
{
  uint i, count = 0;
  for (i = 0; i < n_nbrs; i++)
    if (states [i] == CUZ_ON)
      count++;
  return (count % 2 == 0) ? CUZ_OFF : CUZ_ON;
}

//! Update state based on conway's game of life
//
// \param states Array of neighbor states
// \param n_nbrs Number of neighbors in neighborhood
// \return Next state
cuz_state_t cuz_conways_life (cuz_state_t* states, uint n_nbrs)
{
  uint i, count = 0;

  for (i = 1; i < n_nbrs; i++)
    if (states [i] == CUZ_ON)
      count++;
  
  if (states [0] == CUZ_ON)
    return (count == 2, count == 3) ? CUZ_ON : CUZ_OFF;
  return (count == 3) ? CUZ_ON : CUZ_OFF;
}
