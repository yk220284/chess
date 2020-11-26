#pragma once
#include <memory>
#include <array>
#include <string>
#include "piece.hpp"
std::string DEFAULT_FILE("standard.pos");
class Board
{
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> board{nullptr};

public:
    /* Set board using a file contains initial position of pieces.
    This way is more flexible as we can have different initial positions to 
    debug. */
    void setBoard(std::string const &fileName = DEFAULT_FILE);
    Board(std::string const &fileName);
    Board();
};