#include "piece.hpp"
/*----------Piece----------*/
std::unique_ptr<Piece> createPiece(Color color, PieceType pieceType)
{
    switch (pieceType)
    {
    case PieceType::king:
        return std::make_unique<King>(color, pieceType); // return rvalue, move semantics.
    case PieceType::rook:
        return std::make_unique<Rook>(color, pieceType);
    case PieceType::bishop:
        return std::make_unique<Bishop>(color, pieceType);
    case PieceType::queen:
        return std::make_unique<Queen>(color, pieceType);
    case PieceType::knight:
        return std::make_unique<Knight>(color, pieceType);
    case PieceType::pawn:
        return std::make_unique<Pawn>(color, pieceType);
    }
}
/* Const accessor to color and pieceType. */
Color const &Piece::getColor()
{
    return color;
}
PieceType const &Piece::getPieceType()
{
    return pieceType;
}

/*----------King----------*/
std::unique_ptr<std::vector<Coor>> King::findPath(std::string const &start, std::string const &end) { return true; }
/*----------Pawn----------*/
std::unique_ptr<std::vector<Coor>> Pawn::findPath(std::string const &start, std::string const &end) { return true; }
/*----------Knight----------*/
std::unique_ptr<std::vector<Coor>> Knight::findPath(std::string const &start, std::string const &end) { return true; }
/*----------Rook----------*/
std::unique_ptr<std::vector<Coor>> Rook::findPath(std::string const &start, std::string const &end) { return true; }
/*----------Bishop----------*/
std::unique_ptr<std::vector<Coor>> Bishop::findPath(std::string const &start, std::string const &end) { return true; }
/*----------Queen----------*/
std::unique_ptr<std::vector<Coor>> Queen::findPath(std::string const &start, std::string const &end) { return true; }
