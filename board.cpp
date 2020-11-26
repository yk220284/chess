#include "board.hpp"
#include "util.hpp"
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
        std::for_each(tokens.begin() + 2, tokens.end(), [&color, &pieceType](auto const &posStr) {
            Coor coor = convertPos(posStr);
            board[coor.y][coor.x] = std::make_unique<Piece>(color, pieceType);
        });
    }
}
Board::Board(std::string const &fileName)
{
    setBoard(fileName);
}
Board::Board() : Board(DEFAULT_FILE) {}