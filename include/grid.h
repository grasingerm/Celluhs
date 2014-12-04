#ifndef __GRID_H__
#define __GRID_H__

#include "typemods.h"

#define CUZ_PGRID_ELEM_AT(grid, i, j) \
  (*( (grid)->states + ( (j) * (grid)->n_rows ) + (i) ))

#define CUZ_GRID_ELEM_AT(grid, i, j) \
  (*( (grid).states + ( (j) * (grid).n_rows ) + (i) ))

#define CUZ_ELEM_AT(array, i, j, n_rows) (*( (array) + (j) * (n_rows) + (i) ))

enum state
{
  ON,
  OFF,
  SUSPENDED
};

enum direction
{
  SELF,
  EAST,
  NORTH,
  WEST,
  SOUTH,
  NORTHEAST,
  NORTHWEST,
  SOUTHWEST,
  SOUTHEAST
};

typedef uchar state_t;
typedef ulong dim_t;

struct grid
{
  dim_t n_rows;
  dim_t n_cols;
  state_t* states;
};

struct rule
{
  state_t (*f) (state_t*, uint);
  void (*get_nbr_states) (state_t*, struct grid*, dim_t, dim_t, uint);
  dim_t range_i[2]; // start, finish
  dim_t range_j[2]; // start, finish
};

void init_gd (struct grid* gd, dim_t n_rows, dim_t n_cols, 
  struct cuz_err_t* err);
void destroy_gd (struct grid* gd);
void randomize_gd (struct grid* gd);
void print_gd (struct grid* gd);
void step (struct grid* gd, struct rule* rules, uint n_rules, uint n_nbrs,
  struct cuz_err_t* err);

#endif