#pragma once
#include <iostream>
#include <string>

namespace filenames
{
    std::string const DIR = "chessBoardConfig/";
    std::string const DEFALT_CONFIG = DIR + "standard.pos";
    std::string const ONLY_KING = DIR + "onlyking.pos";

} // namespace filenames

enum class Color : char
{
    white = 'w',
    black = 'b'
};
enum class PieceType : char
{
    king = 'K',
    rook = 'R',
    bishop = 'B',
    queen = 'Q',
    knight = 'N',
    pawn = 'P'
};

std::ostream &operator<<(std::ostream &out, Color color);
std::ostream &operator<<(std::ostream &out, PieceType type);

struct Coor
{
    int x;
    int y;
    Coor();
    Coor(int x, int y);
};

Coor convertPos(std::string const &posStr);
std::ostream &operator<<(std::ostream &out, Coor coor);