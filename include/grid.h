#ifndef __GRID_H__
#define __GRID_H__

#include <memory>
#include <vector>

#include "types.h"

namespace cuz
{

typedef std::array <double, 2> pos_t;

enum default_entry_pts
{
  _DEFAULT_EP_SOUTH_EAST,
  _DEFAULT_EP_SOUTH_WEST,
  _DEFAULT_EP_NORTH_WEST,
  _DEFAULT_EP_NORTH_EAST
};

enum class state
{
  ON,
  OFF
};

enum class direction
{
  NONE = -1,
  EAST, 
  SOUTH, 
  WEST, 
  NORTH
};

struct cell
{
  state status;
  pos_t position;
  std::array < std::shared_ptr < cell >, 4 > neighbors;
};

//  TODO: write STL iterator for grid class
class Grid
{
public:
  Grid (const uint rows, const uint cols, const double base, 
    const double height);
  Grid (const uint rows, const uint cols, const double base,
    const double height, const state init_state);
  Grid (const uint rows, const uint cols, const double base,
    const double height, const init::randu_t);
  // TODO: write constructor for defining custom entry cells
  // TODO: write constructor for using custom geometry

  void step (void (*rule) (cell&));
  void step_interior (void (*rule) (cell&));
  void bc (void (*rule) (cell&), const uint entry_idx, const direction dir,
    const uint num_cells);

  uint n_rows;
  uint n_cols;
private:
  std::vector < std::shared_ptr < cell > > entry_cells;
};

  namespace init
  {
    enum class randu_t { randu };

    // TODO: implement cell initializer functions
    /* 
    void runiform (cell* init_cell, const uint seed);
    void runiform (cell* init_cell);
    void rbinomial (cell* init_cell, const uint seed);
    void rbinomial (cell* init_cell);
    */
  }
}

#endif /* __GRID_H__ */