#pragma once
#include <memory>
#include <array>
#include <iostream>
#include <string>
#include "piece.hpp"

class Board
{
    /*  ----2D array holding all the pieces---- 
     * Note smart pointers default initialise to nullptr. */
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> board;
    /* Take a space sperated string specifiying all the positions of a piece. 
     * Place it on board. */
    void placePiece(std::string const line);

public:
    /* ----Configuration File Path---- */
    static std::string const DIR;
    static std::string const DEFALT_CONFIG;
    /* ----Configuration Strings ---- 
     * used when configuration file is not available. */
    static std::vector<std::string> const STANDARD_CONFIG_STR;
    /* Set board using a file/strings (assuming in the right format) 
     * contains initial position of pieces.
     * This way is more flexible as we can have different initial 
     * positions to debug. */
    void setBoard(std::string const &fileName = DEFALT_CONFIG);
    /* Accessor, provide a valid coordinate (Coor object or a valid string)
     * x, y pair, returns a const reference or reference. */
    std::unique_ptr<Piece> const &operator[](Coor const &coor) const;
    std::unique_ptr<Piece> &operator[](Coor const &coor);
    std::unique_ptr<Piece> const &operator[](std::string const &posStr) const;
    std::unique_ptr<Piece> &operator[](std::string const &posStr);
    /* Consturct board with a configuration file. */
    Board(std::string const &fileName = DEFALT_CONFIG);
    /* print board and pieces on it in a human friendly manner. */
    friend std::ostream &operator<<(std::ostream &out, Board const &board);
};