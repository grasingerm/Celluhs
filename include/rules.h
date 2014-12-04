#ifndef __RULES_H__
#define __RULES_H__

#include "grid.h"
#include "rules.h"

uint cuz_vneumann_interior (cuz_state_t* states, struct grid* gd, 
  cuz_dim_t i, cuz_dim_t j);
uint cuz_vneumann_periodic (cuz_state_t* states, struct grid* gd, 
  cuz_dim_t i, cuz_dim_t j);

#endif