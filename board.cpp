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
            Coor coor = convertPos(posStr);
            board[coor.y][coor.x] = createPiece(color, pieceType);
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

                out << static_cast<char>(p->color) << static_cast<char>(p->pieceType) << '|';
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