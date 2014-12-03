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
};

//  TODO: write STL iterator for grid class
template < uint ROWS, uint COLS > class Grid
{
public:
  Grid < ROWS, COLS > (const double base, const double height)
  {
    const auto dx = base / (n_cols-1);
    const auto dy = height / (n_rows-1);

    for (auto i = uint {0}; i < n_cols; i++)
      for (auto j = uint {0}; j < n_rows; j++)
        
  }
  Grid < ROWS, COLS > (const uint rows, const uint cols, const double base,
    const double height, const state init_state);
  Grid < ROWS, COLS > (const uint rows, const uint cols, const double base,
    const double height, const init::randu_t);
  // TODO: write constructor for defining custom entry cells
  // TODO: write constructor for using custom geometry

  void step (void (*rule) (cell&));
  void step_interior (void (*rule) (cell&));
  void bc ((void *rule) (cell&), const pos_t start, 
          (pos_t* incr) (const pos_t&));
  // TODO: consider losing this... reduntant
  inline cell& operator() (const uint i, const uint j)
  {
    return cells [i][j];
  }

  const static uint n_rows = ROWS;
  const static uint n_cols = COLS;
private:
  std::array < std::array < cell, COLS >, ROWS > cells;
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