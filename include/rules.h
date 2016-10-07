#ifndef __RULES_H__
#define __RULES_H__

#include "grid.h"
#include "rules.h"

uint cuz_vneumann_interior(cuz_state_t *states, const struct cuz_grid *const gd,
                           const cuz_dim_t i, const cuz_dim_t j);
uint cuz_vneumann_periodic(cuz_state_t *states, const struct cuz_grid *const gd,
                           const cuz_dim_t i, const cuz_dim_t j);

uint cuz_moore_interior(cuz_state_t *states, const struct cuz_grid *const gd,
                        const cuz_dim_t i, const cuz_dim_t j);
uint cuz_moore_periodic(cuz_state_t *states, const struct cuz_grid *const gd,
                        const cuz_dim_t i, const cuz_dim_t j);

cuz_state_t cuz_fredkins_rule(const cuz_state_t *states, const uint n_nbrs);
cuz_state_t cuz_conways_life(const cuz_state_t *states, const uint n_nbrs);

/*! Initialize all five rules for a full rectangular grid
 *
 * \param rules Array of rules, size > 5
 * \param rule_f Rule function
 * \param nbr_f Root of neighbor function. *Note name will be appended to.
 * \param rows Number of rows in grid
 * \param cols Number of cols in grid
 */
#define CUZ_INIT_ALL_RULES_FULL_RECT(rules, rulef, nbrfi, nbrfp, rows, cols)   \
  do {                                                                         \
    unsigned int k;                                                            \
                                                                               \
    rules[0].f = &rulef;                                                       \
    rules[0].get_nbr_states = &nbrfi;                                          \
    rules[0].range_i[0] = 1;                                                   \
    rules[0].range_i[1] = cols - 2;                                            \
    rules[0].range_j[0] = 1;                                                   \
    rules[0].range_j[1] = rows - 2;                                            \
                                                                               \
    for (k = 1; k < 5; k++) {                                                  \
      rules[k].f = &rulef;                                                     \
      rules[k].get_nbr_states = &nbrfp;                                        \
    }                                                                          \
                                                                               \
    rules[1].range_i[0] = cols - 1;                                            \
    rules[1].range_i[1] = cols - 1;                                            \
    rules[1].range_j[0] = 0;                                                   \
    rules[1].range_j[1] = rows - 1;                                            \
                                                                               \
    rules[2].range_i[0] = 1;                                                   \
    rules[2].range_i[1] = cols - 2;                                            \
    rules[2].range_j[0] = rows - 1;                                            \
    rules[2].range_j[1] = rows - 1;                                            \
                                                                               \
    rules[3].range_i[0] = 0;                                                   \
    rules[3].range_i[1] = 0;                                                   \
    rules[3].range_j[0] = 0;                                                   \
    rules[3].range_j[1] = rows - 1;                                            \
                                                                               \
    rules[4].range_i[0] = 1;                                                   \
    rules[4].range_i[1] = cols - 2;                                            \
    rules[4].range_j[0] = 0;                                                   \
    rules[4].range_j[1] = 0;                                                   \
  } while (0)

#endif
