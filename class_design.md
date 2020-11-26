# Design Plan of Classes

## Spot
Identified by x, y coordinates.
Each may contains a chess piece. 

## Board (The board itself)
Contains 8\*8 spots.
Responsible for initiating pieces.
Responsible for `void setBoard()`.

In configuration file.
```
w P A2 B2 C2 D2 E2 F2 G2 H2
```
stand for have `white` `Pawn` in squares `A2 B2 C2 D2 E2 F2 G2 H2`.
```
b Q D8 
```
stand for have `black` `Queen` in square `D8`.

## ChessBoard (More like Game, I didn't choose the name ;-()
Determining game status.

Interface for submitMove and resetBoard.


## Player
```cpp
bool isWhite;
bool inChkeck;
Player* Oponent;
bool validMove();
bool submitMove(Board&, Spot& const start, Spot& const end);
bool inCheck();
// See if this move will result me in check.
```
1. check if there is a piece
2. check if piece is mine
3. check if there are pieces between two spots and if the end spot contains my piece.
4. check if start and end are the same spot.



## Piece
A piece don't need to know its spot. Spot records if and what piece is on it.
```cpp
bool isKilled;
bool isWhite;
string name;
virtual bool move(Board&, Spot start, Spot end);
// Return false if it is a legal move for this type of piece. Else return true and make the move.
```
### King (K)
```cpp
bool castled;
bool moved;
bool isValidCastling(Spot start, Spot end);
```
### Knight (N)

### Bishop: virtual Piece (B)
So queen can inherit from both of them.
### Rook: virtual Piece (R)
Similarly.
### Queen: Bishop, Rook (Q)

### Pawn (P)

