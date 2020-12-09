#include <iostream>
#include <string>
#pragma once

/* ----Invalid Move Error Code---- */
enum class InvalidMove : int {
    NO_ERROR = 0,
    INVALID_POS,
    NO_PIECE,
    OPPONENT_PIECE,
    STATIONARY_MOVE,
    ILLEGAL_PIECE_MOVE,
    BLOCK,
    CAPTURE_OWN,
    SELF_IN_CHECK,
    INVALID_CASTLE
};

/* ----Piece/Player Color---- */
enum class Color : char { white = 'w', black = 'b' };
std::ostream& operator<<(std::ostream& out, Color color);

/* ----Piece Type---- */
enum class PieceType : char {
    king = 'K',
    rook = 'R',
    bishop = 'B',
    queen = 'Q',
    knight = 'N',
    pawn = 'P'
};
std::ostream& operator<<(std::ostream& out, PieceType type);

/* ----Coordinates on Board---- */
struct Coor {
    int x;
    int y;
    Coor();
    Coor(int x, int y);
    // Initialization given a legal string is provided.
    explicit Coor(std::string const& posStr);
    bool withInBoard() const;
    std::string str() const;
    friend std::ostream& operator<<(std::ostream& out, Coor const& coor);
    friend Coor operator+(Coor const& lhs, Coor const& rhs);
    friend bool operator==(Coor const& lhs, Coor const& rhs);
    friend bool operator!=(Coor const& lhs, Coor const& rhs);
    // Helper function that return one of the 8 directions required
    // to travel from start to end. (not useful for Knights.)
    friend Coor findDirection(Coor const& start, Coor const& end);
    Coor& operator+=(Coor const& rhs);
};
// Check if string posStr represents a valid position on board.
bool validPosStr(std::string const& posStr);