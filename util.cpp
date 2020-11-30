#include "util.hpp"

std::ostream &operator<<(std::ostream &out, Color color)
{
    switch (color)
    {
    case Color::white:
        out << "White";
        break;
    case Color::black:
        out << "Black";
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
Coor::Coor() : Coor(8, 8) {} // Given no coordinates provided, both initialied to illegal values.
Coor::Coor(std::string const &posStr) : Coor(posStr[0] - 'A', posStr[1] - '1') {}
bool Coor::withInBoard() const
{
    return (x >= 0) && (x < 8) && (y >= 0) && (y < 8);
}
std::string Coor::str() const
{
    return std::string({static_cast<char>('A' + x), static_cast<char>('1' + y)});
}
std::ostream &operator<<(std::ostream &out, Coor const &coor)
{
    out << coor.str();
    return out;
}
bool validPosStr(std::string const &posStr)
{
    if (posStr.size() != 2)
    {
        std::cerr << "Input position " << posStr << " has length not equal to 2\n";
        return false;
    }
    Coor coor{posStr};
    if (!coor.withInBoard())
    {
        std::cerr << "Input position " << posStr << " is not a valid position on board\n";
        return false;
    }
    return true;
}
Coor operator+(Coor const &lhs, Coor const &rhs)
{
    auto rlt = lhs;
    rlt.x += rhs.x;
    rlt.y += rhs.y;
    return rlt;
}
Coor &Coor::operator+=(Coor const &rhs)
{
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}
bool operator==(Coor const &lhs, Coor const &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
bool operator!=(Coor const &lhs, Coor const &rhs)
{
    return !(lhs == rhs);
}
