#include "board.hpp"
#include "piece.hpp"
#include "util.hpp"
#include <algorithm>
#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>
/* configurations */
std::string const Board::DIR = "chessBoardConfig/";
std::string const Board::DEFALT_CONFIG = DIR + "standard.pos";
std::vector<std::string> const Board::STANDARD_CONFIG_STR = {
    "w P A2 B2 C2 D2 E2 F2 G2 H2",
    "w R A1 H1",
    "w N B1 G1",
    "w B C1 F1",
    "w Q D1",
    "w K E1",
    "b P A7 B7 C7 D7 E7 F7 G7 H7",
    "b R A8 H8",
    "b N B8 G8",
    "b B C8 F8",
    "b Q D8 ",
    "b K E8"};

/* set board */
void Board::placePiece(std::string const line)
{
    std::istringstream iss{line};
    std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                    std::istream_iterator<std::string>{}};
    // Note tokens[0] is a string of length 1.
    auto color = static_cast<Color>(tokens[0][0]);
    // Similarly.
    auto pieceType = static_cast<PieceType>(tokens[1][0]);
    // The first two tokens specifies color and pieceType,
    // positions start from the third entry.
    std::for_each(tokens.begin() + 2, tokens.end(), [&](auto const& posStr) {
        (*this)[posStr] = createPiece(color, pieceType);
    });
}
void Board::setBoard(std::string const& fileName)
{
    board = std::array<std::array<std::unique_ptr<Piece>, 8>, 8>();
    std::ifstream infile(fileName);
    // config file exists.
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            placePiece(line);
        }
        infile.close();
    }
    // Cannot open file, use standard config strings instead
    else {
        for (auto const& line : STANDARD_CONFIG_STR) {
            placePiece(line);
        }
    }
}
Board::Board(std::string const& fileName) { setBoard(fileName); }

/* print out board */
std::ostream& operator<<(std::ostream& out, Board const& board)
{
    out << "\n +--+--+--+--+--+--+--+--+\n";
    for (int i = 7; i >= 0; i--) {
        auto const& row = board.board[i];
        out << i + 1 << '|';
        for (auto const& p : row) {
            if (p) {

                out << static_cast<char>(p->getColor())
                    << static_cast<char>(p->getPieceType()) << '|';
            }
            else {
                out << "  |";
            }
        }
        out << "\n +--+--+--+--+--+--+--+--+\n";
    }
    out << " |A |B |C |D |E |F |G |H |\n";

    return out;
}
/* ----Accessors---- */
std::unique_ptr<Piece> const& Board::operator[](Coor const& coor) const
{
    return board[coor.y][coor.x];
}
std::unique_ptr<Piece>& Board::operator[](Coor const& coor)
{
    return board[coor.y][coor.x];
}
std::unique_ptr<Piece> const& Board::operator[](std::string const& posStr) const
{
    return (*this)[Coor(posStr)];
}
std::unique_ptr<Piece>& Board::operator[](std::string const& posStr)
{
    return (*this)[Coor(posStr)];
}