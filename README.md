Celluhs
=======

Parallel and extendable cellular automata library

Examples
--------

Currently, there are two working examples in the test directory. To build:

    cd /path/to/Celluhs_root
    mkdir build
    cd build
    cmake ../ -DCMAKE_BUILD_TYPE=Release
    make

Note that the parallel processing is implemented using OpenMP. In order to
specify the number of threads that you would like to use, you can set the 
environmental variable OMP_NUM_THREADS; e.g.,

    export OMP_NUM_THREADS=4
    
Fredkin's game
______________

    usage: bin/test_fredkin

Fredkin's game has simple rules which leads to self-replication. Each cell with 
an even number of live neighbors will be dead at next time level and alive 
otherwise. An initial pattern of live cells will reproduce itself four times 
after 2^n iterations. For the 'F' pattern in the example, n=2. 
This example was adapted from D.A. Wolf-Gladrow, _Lattice-Gas Cellular Automata 
and Lattice Boltzmann Models_, 2000.

Conway's game of life
_____________________

    usage: bin/test_conway [iterations [rows cols [seed]]]

Conway's game of life hardly needs an introduction. This test binary has a
simple command-line interface for running simulations. The number of iterations,
the number of rows and columns in the grid, and a seed for the C standard
psuedo-random number generator can all be specified.

Also provided is an alternative version, bin/test_conway_quiet, that does not
print the grid after each time step but instead only prints the initial
configuration and final result.

Installation
------------

After building the library, it can be installed in /usr/local/lib and
the headers in /usr/local/include/celluhs using the command:

    make install

Usage
-------
The examples in the test directory provide good starting points for creating
and running a simulation. In order to create your own rules for CA simulations,
use an interface that is consistent with the rules provided in src/rules.c.
A very basic file structure may be as follows:

    #include <stdio.h>
    #include <celluhs/celluhs.h>

    int main() {
      
      struct cuz_err_t err;
      struct cuz_grid gd, temp_gd;
      struct cuz_rule rules[5];

      cuz_init_gd (&gd, rows, cols, &err);
      cuz_init_gd (&temp_gd, rows, cols, &err2);
      
      // some more initialization ...

      // simulate 100 iterations
      for (int i = 0; i < 100; ++i) {
        cuz_step_gd (&gd, &temp_gd, rules, 5, 5, &err);
        
        if (err.code != CUZ_SUCCESS)
        {
          fprintf (stderr, "Failed step %u\n", k);
          fputs (err.msg, stderr);
        }
      }

      // some post processing / visualization

      cuz_destroy_gd (&gd);
      cuz_destroy_gd (&temp_gd);

      return 0;
    }
