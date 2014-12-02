#include "grid.h"

namespace cuz
{

// static cast direction enums to integrals for array indexing
const static auto east_idx = to_integral (EAST);
const static auto south_idx = to_integral (SOUTH);
const static auto west_idx = to_integral (WEST);
const static auto north_idx = to_integral (NORTH);

//! Construct a rectangular grid, default entry points are SE, SW, NW, NE
//
//  \param rows Number of rows of cells
//  \param cols Number of cols of cells
//  \param base Dimension of rectangle in x-direction
//  \param height Dimesion of rectangle in y-direction
//  \return Grid
Grid::Grid (const uint rows, const uint cols, const double base, 
  const double height) : n_rows (rows), n_cols (cols)
{
  const static uint num_default_entry_pts = 4;

  const auto dx = base / rows;
  const auto dy = height / cols;

  // default entry pts are SE, SW, NW, and NE with periodic bcs
  entry_cells = std::vector < std::shared_ptr < cell > > 
    (num_default_entry_pts);

  for (auto i = uint {0}; i < num_default_entry_pts; i++)
    entry_cells.emplace_back (new struct cell);

  entry_cells [_DEFAULT_EP_SOUTH_EAST] -> neighbors [east_idx] = 
                                          entry_cells [_DEFAULT_EP_SOUTH_WEST];
  entry_cells [_DEFAULT_EP_SOUTH_EAST] -> neighbors [south_idx] = 
                                          entry_cells [_DEFAULT_EP_NORTH_EAST];

  entry_cells [_DEFAULT_EP_SOUTH_WEST] -> neighbors [west_idx] = 
                                          entry_cells [_DEFAULT_EP_SOUTH_EAST];
  entry_cells [_DEFAULT_EP_SOUTH_WEST] -> neighbors [south_idx] = 
                                          entry_cells [_DEFAULT_EP_NORTH_WEST];

  entry_cells [_DEFAULT_EP_NORTH_WEST] -> neighbors [west_idx] = 
                                          entry_cells [_DEFAULT_EP_NORTH_EAST];
  entry_cells [_DEFAULT_EP_NORTH_WEST] -> neighbors [north_idx] = 
                                          entry_cells [_DEFAULT_EP_SOUTH_WEST];

  entry_cells [_DEFAULT_EP_NORTH_EAST] -> neighbors [east_idx] = 
                                          entry_cells [_DEFAULT_EP_NORTH_WEST];
  entry_cells [_DEFAULT_EP_NORTH_EAST] -> neighbors [north_idx] = 
                                          entry_cells [_DEFAULT_EP_SOUTH_EAST];

  auto curr_east_cell = entry_cells [_DEFAULT_EP_SOUTH_EAST];
  auto curr_west_cell = entry_cells [_DEFAULT_EP_SOUTH_WEST];
  for (auto j = uint {1}; j < rows-1; j++)
  {
    curr_east_cell -> neighbors [north_idx] = 
                      std::shared_ptr < cell > (new cell);
    curr_west_cell -> neighbors [north_idx] = 
                      std::shared_ptr < cell > (new cell);

    curr_east_cell -> neighbors [north_idx] -> neighbors [south_idx] =
                                      curr_east_cell;
    curr_east_cell -> neighbors [north_idx] -> neighbors [east_idx] =
                                      curr_west_cell -> neighbors [north_idx];

    curr_west_cell -> neighbors [north_idx] -> neighbors [south_idx] =
                                      curr_west_cell;
    curr_west_cell -> neighbors [north_idx] -> neighbors [west_idx] =
                                      curr_east_cell -> neighbors [north_idx];
  }

  for (auto j = uint {0}; j < rows; j++)
  {
    for (auto i = uint {1}; )
  }
}

}