#ifndef __GRID_H__
#define __GRID_H__

#include "typemods.h"

#define CUZ_PGRID_ELEM_AT(grid, i, j) \
  *( (grid)->states + ( (j) * (grid)->n_rows ) + (i) )

#define CUZ_GRID_ELEM_AT(grid, i, j) \
  *( (grid).states + ( (j) * (grid).n_rows ) + (i) )

#define CUZ_ELEM_AT(array, i, j, n_rows) (*( (array) + (j) * (n_rows) + (i) ))

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
  cuz_state_t (*f) (cuz_state_t*, uint);
  uint (*get_nbr_states) (cuz_state_t*, struct cuz_grid*, cuz_dim_t, cuz_dim_t);
  cuz_dim_t range_i[2]; // start, finish
  cuz_dim_t range_j[2]; // start, finish
};

void cuz_init_gd (struct cuz_grid* gd, cuz_dim_t n_rows, cuz_dim_t n_cols, 
  struct cuz_err_t* err);
void cuz_destroy_gd (struct cuz_grid* gd);
void cuz_randomize_gd (struct cuz_grid* gd);
void cuz_fill_gd (struct cuz_grid* gd, cuz_state_t s);
void cuz_fill_pat_gd (struct cuz_grid* gd, cuz_state_t* ss, uint ns);
void cuz_print_gd (struct cuz_grid* gd);
void cuz_printf_gd (struct cuz_grid* gd, void (*stformat) (cuz_state_t, char*));
void cuz_step_gd (struct cuz_grid* gd, struct cuz_rule* rules, uint n_rules, 
  uint n_nbrs, struct cuz_err_t* err);

#endif
