#ifndef __GRID_H__
#define __GRID_H__

#include "types.h"

typedef std::array <double, 2> pos_t

struct cell
{
    state_t state;
    pos_t position;
};

template < class T, f_uint_t ROWS, f_uint_t COLS >
class Grid
{

};

#endif /* __GRID_H__ */