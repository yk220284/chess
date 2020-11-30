#include "piece.hpp"
#include <algorithm>
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
Coor Piece::findDirection(Coor const &start, Coor const &end)
{
    auto dir = [](int s, int e) {
        if (s < e)
        {
            return 1;
        }
        else if (s == e)
        {
            return 0;
        }
        else // s > e
        {
            return -1;
        }
    };
    return Coor(dir(start.x, end.x), dir(start.y, end.y));
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
    Coor const startCoor{start};
    Coor const endCoor{end};
    Path path{nullptr};
    auto direction = findDirection(startCoor, endCoor);
    if (std::find(directions.begin(), directions.end(), direction) != directions.end())
    {
        path = std::make_unique<std::vector<Coor>>();
        auto curCoor = startCoor + direction;
        while (curCoor != endCoor)
        {
            path->emplace_back(curCoor);
            curCoor += direction;
        }
    }
    return path;
}
std::vector<Coor> Rook::potentialEndPositions(std::string const &start)
{
    std::vector<Coor> positions;
    Coor const startCoor(start);
    std::for_each(directions.begin(), directions.end(), [&positions, &startCoor](auto const &direction) {
        auto curCoor = startCoor + direction;
        while (curCoor.withInBoard())
        {
            positions.emplace_back(curCoor);
            curCoor += direction;
        }
    });
    return positions;
}
/*----------Bishop----------*/
Piece::Path Bishop::findPath(std::string const &start, std::string const &end) {}
std::vector<Coor> Bishop::potentialEndPositions(std::string const &start) {}
/*----------Queen----------*/
Piece::Path Queen::findPath(std::string const &start, std::string const &end) {}
std::vector<Coor> Queen::potentialEndPositions(std::string const &start) {}
