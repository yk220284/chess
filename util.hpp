#include <iostream>
#include <string>
#pragma once

/* ----Configuration Files---- */
namespace filenames
{
    std::string const DIR = "chessBoardConfig/";
    std::string const DEFALT_CONFIG = DIR + "standard.pos";
    std::string const ONLY_KING = DIR + "onlyking.pos";
    std::string const TEST_ROOK = DIR + "testRook.pos";
    std::string const IN_CHECK = DIR + "inCheck.pos";
} // namespace filenames

/* ----Invalid Move Error Code---- */
enum class InvalidMove : int
{
    NO_ERROR = 0,
    INVALID_POS,
    NO_PIECE,
    OPPONENT_PIECE,
    STATIONARY_MOVE,
    ILLEGAL_PIECE_MOVE,
    BLOCK,
    CAPTURE_OWN,
    SELF_IN_CHECK
};

/* ----Piece/Player Color---- */
enum class Color : char
{
    white = 'w',
    black = 'b'
};
std::ostream &operator<<(std::ostream &out, Color color);

/* ----Piece Type---- */
enum class PieceType : char
{
    king = 'K',
    rook = 'R',
    bishop = 'B',
    queen = 'Q',
    knight = 'N',
    pawn = 'P'
};
std::ostream &operator<<(std::ostream &out, PieceType type);

/* ----Coordinates on Board---- */
struct Coor
{
    int x;
    int y;
    Coor();
    Coor(int x, int y);
    // Initialisation given a legal string is provided.
    explicit Coor(std::string const &posStr);
    bool withInBoard() const;
    std::string str() const;
    friend std::ostream &operator<<(std::ostream &out, Coor const &coor);
    friend Coor operator+(Coor const &lhs, Coor const &rhs);
    friend bool operator==(Coor const &lhs, Coor const &rhs);
    friend bool operator!=(Coor const &lhs, Coor const &rhs);
    Coor &operator+=(Coor const &rhs);
};
// Check if string posStr represents a valid position on board.
bool validPosStr(std::string const &posStr);