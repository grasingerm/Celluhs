#include "rules.h"
#include "grid.h"

#define N_VNEUMANN(rank) (4 * (rank) + 1)
#define N_MOORE(rank) ((2 * rank + 1) * (2 * rank + 1))

/*! (Without checking for bounds) get von Neumann neighborhood of rank 1
 *
 * \param states Array in which to store von Neumann neighborhood
 * \param gd Pointer to grid
 * \param i Column of cell
 * \param j Row of cell
 * \return Number of neighbors in neighborhood
 */
uint cuz_vneumann_interior(cuz_state_t *states, const struct cuz_grid *const gd,
                           const cuz_dim_t i, const cuz_dim_t j) {
  states[0] = CUZ_PGRID_ELEM_AT(gd, i, j);
  states[1] = CUZ_PGRID_ELEM_AT(gd, i + 1, j);
  states[2] = CUZ_PGRID_ELEM_AT(gd, i, j + 1);
  states[3] = CUZ_PGRID_ELEM_AT(gd, i - 1, j);
  states[4] = CUZ_PGRID_ELEM_AT(gd, i, j - 1);

  return N_VNEUMANN(1);
}

/*! Get von Neumann neighborhood of rank 1 using peroidicity at boundaries
 *
 * \param states Array in which to store von Neumann neighborhood
 * \param gd Pointer to grid
 * \param i Column of cell
 * \param j Row of cell
 * \return Number of neighbors in neighborhood
 */
uint cuz_vneumann_periodic(cuz_state_t *states, const struct cuz_grid *const gd,
                           const cuz_dim_t i, const cuz_dim_t j) {
  states[0] = CUZ_PGRID_ELEM_AT(gd, i, j);
  states[1] = (i + 1 < gd->n_cols) ? CUZ_PGRID_ELEM_AT(gd, i + 1, j)
                                   : CUZ_PGRID_ELEM_AT(gd, 0, j);
  states[2] = (j + 1 < gd->n_rows) ? CUZ_PGRID_ELEM_AT(gd, i, j + 1)
                                   : CUZ_PGRID_ELEM_AT(gd, i, 0);
  states[3] = (i > 0) ? CUZ_PGRID_ELEM_AT(gd, i - 1, j)
                      : CUZ_PGRID_ELEM_AT(gd, gd->n_cols - 1, j);
  states[4] = (j > 0) ? CUZ_PGRID_ELEM_AT(gd, i, j - 1)
                      : CUZ_PGRID_ELEM_AT(gd, i, gd->n_rows - 1);

  return N_VNEUMANN(1);
}

/*! (Without checking for bounds) get von Neumann neighborhood of rank 1
 *
 * \param states Array in which to store Moore neighborhood
 * \param gd Pointer to grid
 * \param i Column of cell
 * \param j Row of cell
 * \return Number of neighbors in neighborhood
 */
uint cuz_moore_interior(cuz_state_t *states, const struct cuz_grid *const gd,
                        const cuz_dim_t i, const cuz_dim_t j) {
  states[0] = CUZ_PGRID_ELEM_AT(gd, i, j);
  states[1] = CUZ_PGRID_ELEM_AT(gd, i + 1, j);
  states[2] = CUZ_PGRID_ELEM_AT(gd, i, j + 1);
  states[3] = CUZ_PGRID_ELEM_AT(gd, i - 1, j);
  states[4] = CUZ_PGRID_ELEM_AT(gd, i, j - 1);
  states[5] = CUZ_PGRID_ELEM_AT(gd, i + 1, j + 1);
  states[6] = CUZ_PGRID_ELEM_AT(gd, i - 1, j + 1);
  states[7] = CUZ_PGRID_ELEM_AT(gd, i - 1, j - 1);
  states[8] = CUZ_PGRID_ELEM_AT(gd, i + 1, j - 1);

  return N_MOORE(1);
}

/*! Get von Neumann neighborhood of rank 1 using peroidicity at boundaries
 *
 * \param states Array in which to store von Neumann neighborhood
 * \param gd Pointer to grid
 * \param i Column of cell
 * \param j Row of cell
 * \return Number of neighbors in neighborhood
 */
uint cuz_moore_periodic(cuz_state_t *states, const struct cuz_grid *const gd,
                        const cuz_dim_t i, const cuz_dim_t j) {
  states[0] = CUZ_PGRID_ELEM_AT(gd, i, j);
  states[1] = (i + 1 < gd->n_cols) ? CUZ_PGRID_ELEM_AT(gd, i + 1, j)
                                   : CUZ_PGRID_ELEM_AT(gd, 0, j);
  states[2] = (j + 1 < gd->n_rows) ? CUZ_PGRID_ELEM_AT(gd, i, j + 1)
                                   : CUZ_PGRID_ELEM_AT(gd, i, 0);
  states[3] = (i > 0) ? CUZ_PGRID_ELEM_AT(gd, i - 1, j)
                      : CUZ_PGRID_ELEM_AT(gd, gd->n_cols - 1, j);
  states[4] = (j > 0) ? CUZ_PGRID_ELEM_AT(gd, i, j - 1)
                      : CUZ_PGRID_ELEM_AT(gd, i, gd->n_rows - 1);
  states[5] = CUZ_PGRID_ELEM_AT(gd, ((i + 1 < gd->n_cols) ? i + 1 : 0),
                                ((j + 1 < gd->n_rows) ? j + 1 : 0));
  states[6] = CUZ_PGRID_ELEM_AT(gd, ((i > 0) ? i - 1 : gd->n_cols - 1),
                                ((j + 1 < gd->n_rows) ? j + 1 : 0));
  states[7] = CUZ_PGRID_ELEM_AT(gd, ((i > 0) ? i - 1 : gd->n_cols - 1),
                                ((j > 0) ? j - 1 : gd->n_rows - 1));
  states[8] = CUZ_PGRID_ELEM_AT(gd, ((i + 1 < gd->n_cols) ? i + 1 : 0),
                                ((j > 0) ? j - 1 : gd->n_rows - 1));

  return N_MOORE(1);
}

/*! Update state based on fredkin's rule
 *
 * \param states Array of neighbor states
 * \param n_nbrs Number of neighbors in neighborhood
 * \return Next state
 */
cuz_state_t cuz_fredkins_rule(const cuz_state_t *states, const uint n_nbrs) {
  uint i, count = 0;
  for (i = 1; i < n_nbrs; i++)
    if (states[i] == CUZ_ON)
      count++;
  return (count % 2 == 0) ? CUZ_OFF : CUZ_ON;
}

/*! Update state based on conway's game of life
 *
 * \param states Array of neighbor states
 * \param n_nbrs Number of neighbors in neighborhood
 * \return Next state
 */
cuz_state_t cuz_conways_life(const cuz_state_t *states, const uint n_nbrs) {
  uint i, count = 0;

  for (i = 1; i < n_nbrs; i++)
    if (states[i] == CUZ_ON)
      count++;

  if (states[0] == CUZ_ON)
    return (count == 2 || count == 3) ? CUZ_ON : CUZ_OFF;
  return (count == 3) ? CUZ_ON : CUZ_OFF;
}
