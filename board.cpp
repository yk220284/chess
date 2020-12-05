#include "board.hpp"
#include "util.hpp"
#include "piece.hpp"
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>
void Board::setBoard(std::string const &fileName)
{
    board = std::array<std::array<std::unique_ptr<Piece>, 8>, 8>();
    std::ifstream infile(fileName);
    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss{line};
        std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                        std::istream_iterator<std::string>{}};
        auto color = static_cast<Color>(tokens[0][0]);         // Note tokens[0] is a string of length 1.
        auto pieceType = static_cast<PieceType>(tokens[1][0]); // Similarly.
        std::for_each(tokens.begin() + 2, tokens.end(), [&](auto const &posStr) {
            (*this)[posStr] = createPiece(color, pieceType);
        });
    }
}
Board::Board(std::string const &fileName)
{
    setBoard(fileName);
}
std::ostream &operator<<(std::ostream &out, Board const &board)
{
    out << "\n +--+--+--+--+--+--+--+--+\n";
    for (int i = 7; i >= 0; i--)
    {
        auto const &row = board.board[i];
        out << i + 1 << '|';
        for (auto const &p : row)
        {
            if (p)
            {

                out << static_cast<char>(p->getColor())
                    << static_cast<char>(p->getPieceType()) << '|';
            }
            else
            {
                out << "  |";
            }
        }
        out << "\n +--+--+--+--+--+--+--+--+\n";
    }
    out << " |A |B |C |D |E |F |G |H |\n";

    return out;
}
/* ----Accessors---- */
std::unique_ptr<Piece> const &Board::operator[](Coor const &coor) const
{
    return board[coor.y][coor.x];
}

std::unique_ptr<Piece> &Board::operator[](Coor const &coor)
{
    return board[coor.y][coor.x];
}
std::unique_ptr<Piece> const &Board::operator[](std::string const &posStr) const
{
    return (*this)[Coor(posStr)];
}
std::unique_ptr<Piece> &Board::operator[](std::string const &posStr)
{
    return (*this)[Coor(posStr)];
}