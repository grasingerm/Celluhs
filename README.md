<script type="text/javascript" 
src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=default"></script>

Celluhs
=======

Fun with cellular automata

Examples
--------

Currently the best working example is test_fredkins. To build:

    cd /path/to/Celluhs_root
    mkdir build
    cd build
    cmake ../test/ -D CMAKE_BUILD_TYPE=release
    make
    bin/test_fredkin
    
Fredkin's game has simple rules which leads to self-replication. Each cell with 
an even number of live neighbors will be dead at next time level and alive 
otherwise. An initial pattern of live cells will reproduce itself four times 
after $$2^n$$ iterations. For the 'F' pattern in the example, $$n=2$$. 
This example was adapted from D.A. Wolf-Gladrow, _Lattice-Gas Cellular Automata 
and Lattice Boltzmann Models_, 2000.