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
/*----------King----------*/
bool King::validMove(std::string const &start, std::string const &end) { return true; }
/*----------Pawn----------*/
bool Pawn::validMove(std::string const &start, std::string const &end) { return true; }
/*----------Knight----------*/
bool Knight::validMove(std::string const &start, std::string const &end) { return true; }
/*----------Rook----------*/
bool Rook::validMove(std::string const &start, std::string const &end) { return true; }
/*----------Bishop----------*/
bool Bishop::validMove(std::string const &start, std::string const &end) { return true; }
/*----------Queen----------*/
bool Queen::validMove(std::string const &start, std::string const &end) { return true; }
