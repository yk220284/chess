#include "piece.hpp"
#include <algorithm>
/*--------------------------Piece--------------------------*/
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
Color const &Piece::getColor()
{
    return color;
}
PieceType const &Piece::getPieceType()
{
    return pieceType;
}
void Piece::markMoved()
{
    moved = true;
}
bool Piece::hasMoved() const
{
    return moved;
}
/*--------------------------King--------------------------*/
std::vector<Coor> const King::directions =
    {Coor(0, 1), Coor(1, 0), Coor(0, -1), Coor(-1, 0),
     Coor(1, 1), Coor(1, -1), Coor(-1, -1), Coor(-1, 1)};
Piece::Path King::findPath(std::string const &start, std::string const &end)
{
    Coor const startCoor{start};
    Coor const endCoor{end};
    Path path{nullptr};
    if (abs(endCoor.x - startCoor.x) <= 1 && abs(endCoor.y - startCoor.y) <= 1)
    {
        path = std::make_unique<std::vector<Coor>>();
    }
    return path;
}
std::vector<Coor> King::potentialEndPositions(std::string const &start)
{
    Coor const startCoor{start};
    std::vector<Coor> positions;
    // Note: if you are in check, you cannot castle,
    // so the potentialEnds don't include castle movement.
    for (auto const &direction : directions)
    {
        positions.emplace_back(direction + startCoor);
    }
    return positions;
}
/*--------------------------Pawn--------------------------*/
Piece::Path Pawn::findPath(std::string const &start, std::string const &end) {}
std::vector<Coor> Pawn::potentialEndPositions(std::string const &start) {}
/*--------------------------Knight--------------------------*/
Piece::Path Knight::findPath(std::string const &start, std::string const &end) {}
std::vector<Coor> Knight::potentialEndPositions(std::string const &start) {}
/*--------------------------Rook--------------------------*/
std::vector<Coor> const Rook::directions = {Coor(0, 1), Coor(1, 0), Coor(-1, 0), Coor(0, -1)};
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
/*--------------------------Bishop--------------------------*/
Piece::Path Bishop::findPath(std::string const &start, std::string const &end) {}
std::vector<Coor> Bishop::potentialEndPositions(std::string const &start) {}
/*--------------------------Queen--------------------------*/
Piece::Path Queen::findPath(std::string const &start, std::string const &end) {}
std::vector<Coor> Queen::potentialEndPositions(std::string const &start) {}
