#pragma once
#include <memory>
#include <array>
#include <iostream>
#include <string>
#include "piece.hpp"

class Board
{
    /* Smart pointers default initialise to nullptr. */
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> board;
    /* Take a space sperated string specifiying all the positions of a piece. Place it on board. */
    void placePiece(std::string const line);
    std::vector<std::string> const static STANDARD_CONFIG_STR;

public:
    /* Set board using a file (assuming in the right format) contains initial position of pieces.
    This way is more flexible as we can have different initial positions to 
    debug. */
    void setBoard(std::string const &fileName = filenames::DEFALT_CONFIG);
    /* Accessor, provide a valid coordinate (Coor object or a valid string)
    x, y pair, returns a const reference or reference. */
    std::unique_ptr<Piece> const &operator[](Coor const &coor) const;
    std::unique_ptr<Piece> &operator[](Coor const &coor);
    std::unique_ptr<Piece> const &operator[](std::string const &posStr) const;
    std::unique_ptr<Piece> &operator[](std::string const &posStr);
    Board(std::string const &fileName = filenames::DEFALT_CONFIG);
    friend std::ostream &operator<<(std::ostream &out, Board const &board);
};