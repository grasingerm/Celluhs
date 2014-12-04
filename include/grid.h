#ifndef __GRID_H__
#define __GRID_H__

#include "typemods.h"

#define M_PGRID_ELEM_AT(grid, i, j) \
  (*( (grid)->states + ( (j) * (grid)->n_rows ) + (i) ))

#define M_GRID_ELEM_AT(grid, i, j) \
  (*( (grid).states + ( (j) * (grid).n_rows ) + (i) ))

enum state
{
  ON,
  OFF,
  SUSPENDED
};

struct grid
{
  ulonglong n_rows;
  ulonglong n_cols;
  uint* states;
};

void init_gd (struct grid* gd, ulonglong n_rows, ulonglong n_cols, 
  struct cuz_err_t* err);
void destroy_gd (struct grid* gd);
void randomize_gd (struct grid* gd);
void print_gd (struct grid* gd);
void step (struct grid* gd, void (*rule) (uint i, uint j), 
  struct cuz_err_t* err);

#endif