#pragma once
#include "util.hpp"
#include <memory>
/*----------Piece----------*/
class Piece
{

public:
    Color color;
    PieceType pieceType;
    Piece() = default;
    Piece(Color const &color, PieceType const &pieceType) : color(color), pieceType(pieceType) {}
    virtual ~Piece() = default;
    /* Pure virtual function must be overriden.
    Only check if this move belongs to a set of moves allowed by the piece.
    Information about board is not checked here. */
    virtual bool validMove(std::string const &start, std::string const &end) = 0;
};
/* Create an dynamic object according to the pieceType and return a pointer to it. */
std::unique_ptr<Piece> createPiece(Color color, PieceType pieceType);
/*----------King----------*/
class King : public Piece
{
public:
    King(Color const &color, PieceType const &pieceType) : Piece(color, pieceType) {}
    ~King() = default;
    bool validMove(std::string const &start, std::string const &end);
};
/*----------Pawn----------*/
class Pawn : public Piece
{
public:
    Pawn(Color const &color, PieceType const &pieceType) : Piece(color, pieceType) {}
    ~Pawn() = default;
    bool validMove(std::string const &start, std::string const &end);
};
/*----------Knight----------*/
class Knight : public Piece
{
public:
    Knight(Color const &color, PieceType const &pieceType) : Piece(color, pieceType){};
    ~Knight() = default;
    bool validMove(std::string const &start, std::string const &end);
};
/*----------Rook----------*/
class Rook : virtual public Piece
{
public:
    Rook() = default;
    Rook(Color const &color, PieceType const &pieceType) : Piece(color, pieceType){};
    virtual ~Rook() = default;
    bool validMove(std::string const &start, std::string const &end);
};
/*----------Bishop----------*/
class Bishop : virtual public Piece
{
public:
    Bishop() = default;
    Bishop(Color const &color, PieceType const &pieceType) : Piece(color, pieceType){};
    virtual ~Bishop() = default;
    bool validMove(std::string const &start, std::string const &end);
};
/*----------Queen----------*/
class Queen : public Rook, public Bishop
{
public:
    /* Explicitly calling the constructor of its virtual base class. */
    Queen(Color const &color, PieceType const &pieceType) : Piece(color, pieceType) {}
    ~Queen() = default;
    bool validMove(std::string const &start, std::string const &end);
};
