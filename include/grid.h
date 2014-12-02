#ifndef __GRID_H__
#define __GRID_H__

#include <memory>
#include <vector>
#include "types.h"

typedef std::array <double, 2> pos_t;

enum class state
{
    ON,
    OFF,
    SUSPENDED
};

struct cell
{
    state status;
    pos_t position;
    std::shared_ptr < cell > east_cell;
    std::shared_ptr < cell > west_cell;
    std::shared_ptr < cell > north_cell;
    std::shared_ptr < cell > south_cell;
};

class Grid
{
public:
    Grid (const unsigned int rows, const unsigned int cols) : 

    std::vector < std::shared_ptr < cell > > east_bndry;
    std::vector < std::shared_ptr < cell > > west_bndry;
    unsigned int n_rows;
    unsigned int n_cols;
};

#endif /* __GRID_H__ */