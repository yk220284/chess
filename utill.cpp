#include "util.hpp"

std::ostream &operator<<(std::ostream &out, Color color)
{
    switch (color)
    {
    case Color::white:
        out << "White";
        break;
    case Color::black:
        out << "black";
        break;
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, PieceType type)
{
    switch (type)
    {
    case PieceType::king:
        out << "King";
        break;
    case PieceType::rook:
        out << "Rook";
        break;
    case PieceType::bishop:
        out << "Bishop";
        break;
    case PieceType::queen:
        out << "Queen";
        break;
    case PieceType::knight:
        out << "Knight";
        break;
    case PieceType::pawn:
        out << "Pawn";
        break;
    }
    return out;
}

Coor::Coor(int x, int y) : x(x), y(y) {}
Coor convertPos(std::string const &posStr)
{
    return Coor(posStr[0] - 'A', posStr[1] - '1');
}
std::ostream &operator<<(std::ostream &out, Coor coor)
{
    out << 'A' + coor.x << '1' + coor.y;
    return out;
}