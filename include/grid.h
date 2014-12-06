#ifndef __GRID_H__
#define __GRID_H__

#include "typemods.h"

#define CUZ_PGRID_ELEM_AT(grid, i, j) \
  *( (grid)->states + ( (i) * (grid)->n_cols ) + (j) )

#define CUZ_GRID_ELEM_AT(grid, i, j) \
  *( (grid).states + ( (i) * (grid).n_cols ) + (j) )

#define CUZ_ELEM_AT(array, i, j, n_cols) (*( (array) + (i) * (n_cols) + (j) ))

enum cuz_state
{
  CUZ_OFF,
  CUZ_ON,
  CUZ_SUSPENDED
};

enum cuz_direction
{
  CUZ_SELF,
  CUZ_EAST,
  CUZ_NORTH,
  CUZ_WEST,
  CUZ_SOUTH,
  CUZ_NORTHEAST,
  CUZ_NORTHWEST,
  CUZ_SOUTHWEST,
  CUZ_SOUTHEAST
};

typedef uchar cuz_state_t;
typedef ulong cuz_dim_t;

struct cuz_grid
{
  cuz_dim_t n_rows;
  cuz_dim_t n_cols;
  cuz_state_t* states;
};

struct cuz_rule
{
  cuz_state_t (*f) (const cuz_state_t* states, const uint n_nbrs);
  uint (*get_nbr_states) (cuz_state_t* states, const struct cuz_grid* const gd,
    const cuz_dim_t i, const cuz_dim_t j);
  cuz_dim_t range_i[2]; // start, finish
  cuz_dim_t range_j[2]; // start, finish
};

void cuz_init_gd (struct cuz_grid* gd, const cuz_dim_t n_rows, 
  const cuz_dim_t n_cols, struct cuz_err_t* err);
void cuz_destroy_gd (struct cuz_grid* gd);
void cuz_randomize_gd (struct cuz_grid* gd);
void cuz_fill_gd (struct cuz_grid* gd, const cuz_state_t s);
void cuz_fill_pat_gd (struct cuz_grid* gd, const cuz_state_t* ss, 
  const uint ns);
void cuz_print_gd (const struct cuz_grid* const gd);
void cuz_printf_gd (const struct cuz_grid* const gd, 
  void (*stformat) (const cuz_state_t, char*));
void cuz_step_gd (struct cuz_grid* gd, struct cuz_rule* rules, 
  const uint n_rules, const uint n_nbrs, struct cuz_err_t* err);

#endif
