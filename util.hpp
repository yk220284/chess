#pragma once
#include <iostream>
#include <string>
enum class Color
{
    white,
    black
};
enum class PieceType : char
{
    king = 'k',
    rook = 'r',
    bishop = 'b',
    queen = 'q',
    knight = 'n',
    pawn = 'p'
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