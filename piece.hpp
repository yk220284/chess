#include "util.hpp"
#include <memory>
#include <vector>
#pragma once
/*----------Piece----------*/
class Piece {
    Color color;
    PieceType pieceType;
    bool moved = false;

public:
    typedef std::unique_ptr<std::vector<Coor>> Path;
    Piece() = default;
    Piece(Color const& color, PieceType const& pieceType)
        : color(color), pieceType(pieceType)
    {
    }
    virtual ~Piece() = default;
    // Const accessor to color.
    Color const& getColor();
    // Const accessor to pieceType.
    PieceType const& getPieceType();
    // Mark change the member variable moved to true.
    void markMoved();
    // Access moved member variable.
    bool hasMoved() const;
    // Pure virtual function must be overridden.
    // If there exits a valid path return a pointer to the vector (which may be
    // an empty vector) specifying the path from start to end. Note path does
    // NOT include start and end to save memory. otherwise return a nullptr.
    virtual Path findPath(std::string const& start, std::string const& end) = 0;
    // Pure virtual function must be overridden.
    // Taking a starting position of the piece,
    // Return a vector of positions that this piece has legal move to
    // (i.e. don't consider the situation on the board for now).
    virtual std::vector<Coor>
    potentialEndPositions(std::string const& start) = 0;
};
// Create an dynamic object according to the pieceType and return a pointer to
// it.
std::unique_ptr<Piece> createPiece(Color color, PieceType pieceType);

/*----------King----------*/
class King : public Piece {
    static std::vector<Coor> const directions;

public:
    King(Color const& color, PieceType const& pieceType)
        : Piece(color, pieceType)
    {
    }
    ~King() = default;
    Path findPath(std::string const& start, std::string const& end) override;
    std::vector<Coor> potentialEndPositions(std::string const& start) override;
};
/*----------Pawn----------*/
class Pawn : public Piece {
public:
    Pawn(Color const& color, PieceType const& pieceType)
        : Piece(color, pieceType)
    {
    }
    ~Pawn() = default;
    Path findPath(std::string const& start, std::string const& end) override;
    std::vector<Coor> potentialEndPositions(std::string const& start) override;
};
/*----------Knight----------*/
class Knight : public Piece {
    static std::vector<Coor> const directions;

public:
    Knight(Color const& color, PieceType const& pieceType)
        : Piece(color, pieceType){};
    ~Knight() = default;
    Path findPath(std::string const& start, std::string const& end) override;
    std::vector<Coor> potentialEndPositions(std::string const& start) override;
};

/*----------Rook----------*/
class Rook : virtual public Piece {
    static std::vector<Coor> const directions;

public:
    Rook() = default;
    Rook(Color const& color, PieceType const& pieceType)
        : Piece(color, pieceType){};
    ~Rook() = default;
    Path findPath(std::string const& start, std::string const& end) override;
    std::vector<Coor> potentialEndPositions(std::string const& start) override;
};

/*----------Bishop----------*/
class Bishop : virtual public Piece {
    static std::vector<Coor> const directions;

public:
    Bishop() = default;
    Bishop(Color const& color, PieceType const& pieceType)
        : Piece(color, pieceType){};
    ~Bishop() = default;
    Path findPath(std::string const& start, std::string const& end) override;
    std::vector<Coor> potentialEndPositions(std::string const& start) override;
};
/*----------Queen----------*/
class Queen : public Rook, public Bishop {
public:
    /* Explicitly calling the constructor of its virtual base class. */
    Queen(Color const& color, PieceType const& pieceType)
        : Piece(color, pieceType)
    {
    }
    ~Queen() = default;
    Path findPath(std::string const& start, std::string const& end) override;
    std::vector<Coor> potentialEndPositions(std::string const& start) override;
};