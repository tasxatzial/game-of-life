# Game of Life

The [Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) by John Horton Conway.

Given an initial state of a cellular automaton, the program calculates its state after 50 iterations.

## Implementation

Two versions are provided, one that uses only local variables and one that uses both local and global variables. Both versions behave the same.

Cells are represented by a fixed grid, and any cells located outside the grid are considered dead. The dimensions of the grid are determined by the first line of the input file.

## Compile

* Build the local variables version

```bash
make game_local
```

* Build the global variables version

```bash
make game_global
```

## Typical usage

Read initial state from input_file and write the final state to out_file:

```bash
./game_local input_file out_file
```

## Tests

See [tests](tests). Two input .txt files are provided along with their corresponding .out files after 50 iterations.

## Profiling

'game_local' and 'game_global' been tested for memory leaks with [valgrind](https://valgrind.org/) and [AddressSanitizer](https://github.com/google/sanitizers/wiki/AddressSanitizer).
