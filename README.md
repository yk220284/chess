# Compile and Run
Ideally `cmake` should be used, though a `makefile` is also provided.

## Using `cmake`
```bash
mkdir build
cd build/
cmake ..
cmake --build .
```

### Run unit tests
A unit test in `catch2` is also available.
```bash
# within the build/ directory
ctest 
# or, for verbose output
ctest -v
# or, run executable 
./Tests
```

### Run executable
```bash
# in the build/ directory
./chess
```

## Using `makefile`
Unit tests are not available using `makefile`. In the project root, run
``` bash
make 
./chess
``` 

# Design Plan of Classes
A brief description of the major components.

## Coor
A wrapper of x, y coordinates, can also represent the direction of a move. It's contained in `Util.hpp`. 

## Board (The board itself)
Contains a 8\*8 2D array of pointers to Piece objects.
Responsible for initiating pieces using configuration files/strings.

> In configuration file/string, a line
> ```
> w P A2 B2 C2 D2 E2 F2 G2 H2
> ```
> stand for have `white` `Pawn` in squares `A2 B2 C2 D2 E2 F2 G2 H2`.
> ```
> b Q D8 
> ```
> stand for have `black` `Queen` in square `D8`.

## Piece
An abstract class from which all six types of pieces are inherited. It has no knowledge about `Board`. Hence it's only responsible for validating whether a move is legal regardless of the situation on board. 
> e.g. Pawn class is responsible for checking whether it's asked to move backward, 
> but, say, is not responsible for checking whether it's blocked by another piece.



## Player
The main logic goes in here. It's responsible for 
1. validating a move (checking all the conditions not handled by Piece class)
2. submit a move
3. keep track of whether a player is in check/checkmate.



## ChessBoard (More like a Game class, I didn't choose the name ;-()
It will setup a `Board` two `Player`s and a interface for submitting move.









