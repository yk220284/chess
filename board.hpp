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

public:
    /* Set board using a file (assuming in the right format) contains initial position of pieces.
    This way is more flexible as we can have different initial positions to 
    debug. */
    void setBoard(std::string const &fileName = filenames::DEFALT_CONFIG);
    Board(std::string const &fileName = filenames::DEFALT_CONFIG);
    friend std::ostream &operator<<(std::ostream &out, Board const &board);
};