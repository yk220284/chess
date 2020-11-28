#pragma once
#include "util.hpp"
#include <memory>
#include <vector>
/*----------Piece----------*/
class Piece
{
    Color color;
    PieceType pieceType;

public:
    Piece() = default;
    Piece(Color const &color, PieceType const &pieceType) : color(color), pieceType(pieceType) {}
    virtual ~Piece() = default;
    /* Const accessor to color and pieceType. */
    Color const &getColor();
    PieceType const &getPieceType();
    /* Pure virtual function must be overriden.
        If there exits a valid path return a pointer to the vector specifiying 
        the path from start to end. Note path does NOT include start and end to save memory.
        otherwise return a nullptr. */
    virtual std::unique_ptr<std::vector<Coor>> findPath(std::string const &start, std::string const &end) = 0;
};
/* Create an dynamic object according to the pieceType and return a pointer to it. */
std::unique_ptr<Piece> createPiece(Color color, PieceType pieceType);
/*----------King----------*/
class King : public Piece
{
public:
    King(Color const &color, PieceType const &pieceType) : Piece(color, pieceType) {}
    ~King() = default;
    std::unique_ptr<std::vector<Coor>> findPath(std::string const &start, std::string const &end) override;
};
/*----------Pawn----------*/
class Pawn : public Piece
{
public:
    Pawn(Color const &color, PieceType const &pieceType) : Piece(color, pieceType) {}
    ~Pawn() = default;
    std::unique_ptr<std::vector<Coor>> findPath(std::string const &start, std::string const &end);
};
/*----------Knight----------*/
class Knight : public Piece
{
public:
    Knight(Color const &color, PieceType const &pieceType) : Piece(color, pieceType){};
    ~Knight() = default;
    std::unique_ptr<std::vector<Coor>> findPath(std::string const &start, std::string const &end);
};
/*----------Rook----------*/
class Rook : virtual public Piece
{
public:
    Rook() = default;
    Rook(Color const &color, PieceType const &pieceType) : Piece(color, pieceType){};
    virtual ~Rook() = default;
    std::unique_ptr<std::vector<Coor>> findPath(std::string const &start, std::string const &end);
};
/*----------Bishop----------*/
class Bishop : virtual public Piece
{
public:
    Bishop() = default;
    Bishop(Color const &color, PieceType const &pieceType) : Piece(color, pieceType){};
    virtual ~Bishop() = default;
    std::unique_ptr<std::vector<Coor>> findPath(std::string const &start, std::string const &end);
};
/*----------Queen----------*/
class Queen : public Rook, public Bishop
{
public:
    /* Explicitly calling the constructor of its virtual base class. */
    Queen(Color const &color, PieceType const &pieceType) : Piece(color, pieceType) {}
    ~Queen() = default;
    std::unique_ptr<std::vector<Coor>> findPath(std::string const &start, std::string const &end);
};
