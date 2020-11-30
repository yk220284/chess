#pragma once
#include "util.hpp"
#include <memory>
#include <vector>
/*----------Piece----------*/
class Piece
{
    Color color;
    PieceType pieceType;

protected:
    // Helper function that return one of the 8 directions required
    // to travel from start to end. (not useful for Knights.)
    Coor findDirection(Coor const &start, Coor const &end);
    typedef std::unique_ptr<std::vector<Coor>> Path;

public:
    Piece() = default;
    Piece(Color const &color, PieceType const &pieceType) : color(color), pieceType(pieceType) {}
    virtual ~Piece() = default;
    /* Const accessor to color and pieceType. */
    Color const &getColor();
    PieceType const &getPieceType();
    /* Pure virtual function must be overriden.
        If there exits a valid path return a pointer to the vector (which may be an empty vector) specifiying 
        the path from start to end. Note path does NOT include start and end to save memory.
        otherwise return a nullptr. */
    virtual Path findPath(std::string const &start, std::string const &end) = 0;
    /* Taking a starting position of the piece, 
    Return a vector of positions that this piece has legal move to 
    (i.e. don't consider the situation on the board for now). */
    virtual std::vector<Coor> potentialEndPositions(std::string const &start) = 0;
};
/* Create an dynamic object according to the pieceType and return a pointer to it. */
std::unique_ptr<Piece> createPiece(Color color, PieceType pieceType);
/*----------King----------*/
class King : public Piece
{
public:
    King(Color const &color, PieceType const &pieceType) : Piece(color, pieceType) {}
    ~King() = default;
    Path findPath(std::string const &start, std::string const &end) override;
    std::vector<Coor> potentialEndPositions(std::string const &start) override;
};
/*----------Pawn----------*/
class Pawn : public Piece
{
public:
    Pawn(Color const &color, PieceType const &pieceType) : Piece(color, pieceType) {}
    ~Pawn() = default;
    Path findPath(std::string const &start, std::string const &end) override;
    std::vector<Coor> potentialEndPositions(std::string const &start) override;
};
/*----------Knight----------*/
class Knight : public Piece
{
public:
    Knight(Color const &color, PieceType const &pieceType) : Piece(color, pieceType){};
    ~Knight() = default;
    Path findPath(std::string const &start, std::string const &end) override;
    std::vector<Coor> potentialEndPositions(std::string const &start) override;
};

/*----------Rook----------*/
class Rook : virtual public Piece
{
    std::vector<Coor> directions = {Coor(0, 1), Coor(1, 0), Coor(-1, 0), Coor(0, -1)};

public:
    Rook() = default;
    Rook(Color const &color, PieceType const &pieceType) : Piece(color, pieceType){};
    ~Rook() = default;
    Path findPath(std::string const &start, std::string const &end) override;
    std::vector<Coor> potentialEndPositions(std::string const &start) override;
};
/*----------Bishop----------*/
class Bishop : virtual public Piece
{
public:
    Bishop() = default;
    Bishop(Color const &color, PieceType const &pieceType) : Piece(color, pieceType){};
    ~Bishop() = default;
    Path findPath(std::string const &start, std::string const &end) override;
    std::vector<Coor> potentialEndPositions(std::string const &start) override;
};
/*----------Queen----------*/
class Queen : public Rook, public Bishop
{
public:
    /* Explicitly calling the constructor of its virtual base class. */
    Queen(Color const &color, PieceType const &pieceType) : Piece(color, pieceType) {}
    ~Queen() = default;
    Path findPath(std::string const &start, std::string const &end) override;
    std::vector<Coor> potentialEndPositions(std::string const &start) override;
};
