<script type="text/javascript" 
src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=default"></script>

Celluhs
=======

Fun with cellular automata

Examples
--------

Currently, there are two working examples in the test directory. To build:

    cd /path/to/Celluhs_root
    mkdir build
    cd build
    cmake ../test/ -D CMAKE_BUILD_TYPE=release
    make
    
Fredkin's game
______________

    usage: bin/test_fredkin

Fredkin's game has simple rules which leads to self-replication. Each cell with 
an even number of live neighbors will be dead at next time level and alive 
otherwise. An initial pattern of live cells will reproduce itself four times 
after $$2^n$$ iterations. For the 'F' pattern in the example, $$n=2$$. 
This example was adapted from D.A. Wolf-Gladrow, _Lattice-Gas Cellular Automata 
and Lattice Boltzmann Models_, 2000.

Conway's game of life
_____________________

    usage: bin/test_conway [iterations [rows cols [seed]]]

Conway's game of life hardly needs an introduction. This test binary has a
simple command-line interface for running simulations. The number of iterations,
the number of rows and columns in the grid, and a seed for the C standard
psuedo-random number generator can all be specified.
