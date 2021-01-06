# Game of Life

The [Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) by John Horton Conway.

Given an initial state of a cellular automaton, the program calculates its state after 50 iterations.

## Implementation

Two versions are provided: One that uses only local variables
and one that uses both local and global variables. Both versions behave the same.

## Compile

Use the provided Makefile:

### Build local variables version

```bash
make game_local
```

### Build global variables version

```bash
make game_global
```

## Typical usage

Read initial state from input_file and write the final state to out_file:

```bash
./game_local input_file out_file
```

## Sample files

See [tests](tests).
