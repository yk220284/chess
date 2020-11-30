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
Piece::Path King::findPath(std::string const &start, std::string const &end) {}
std::vector<Coor> King::potentialEndPositions(std::string const &start) {}
/*----------Pawn----------*/
Piece::Path Pawn::findPath(std::string const &start, std::string const &end) {}
std::vector<Coor> Pawn::potentialEndPositions(std::string const &start) {}
/*----------Knight----------*/
Piece::Path Knight::findPath(std::string const &start, std::string const &end) {}
std::vector<Coor> Knight::potentialEndPositions(std::string const &start) {}
/*----------Rook----------*/
Piece::Path Rook::findPath(std::string const &start, std::string const &end)
{
    Coor startCoor{start};
    Coor endCoor{end};
    if (!(startCoor.withInBoard() && endCoor.withInBoard()))
    {
        std::cerr << "Encounter an invalid coordinate\n";
    }
    Path path{nullptr};
    if (startCoor.x == endCoor.x)
    {
        path = std::make_unique<std::vector<Coor>>();
        for (int y = startCoor.y + 1; y < endCoor.y; y++)
        {
            path->emplace_back(Coor(startCoor.x, y));
        }
    }
    if (startCoor.y == endCoor.y)
    {
        path = std::make_unique<std::vector<Coor>>();
    }
    return path;
}
std::vector<Coor> Rook::potentialEndPositions(std::string const &start)
{
}
/*----------Bishop----------*/
Piece::Path Bishop::findPath(std::string const &start, std::string const &end) {}
std::vector<Coor> Bishop::potentialEndPositions(std::string const &start) {}
/*----------Queen----------*/
Piece::Path Queen::findPath(std::string const &start, std::string const &end) {}
std::vector<Coor> Queen::potentialEndPositions(std::string const &start) {}
