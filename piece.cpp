#include "piece.hpp"
#include <algorithm>
/*--------------------------Piece--------------------------*/
std::unique_ptr<Piece> createPiece(Color color, PieceType pieceType)
{
    switch (pieceType) {
    case PieceType::king:
        return std::make_unique<King>(
            color, pieceType); // return rvalue, move semantics.
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
Color const& Piece::getColor() { return color; }
PieceType const& Piece::getPieceType() { return pieceType; }
void Piece::markMoved() { moved = true; }
bool Piece::hasMoved() const { return moved; }
/*--------------------------King--------------------------*/
std::vector<Coor> const King::directions = {
    Coor(0, 1), Coor(1, 0),  Coor(0, -1),  Coor(-1, 0),
    Coor(1, 1), Coor(1, -1), Coor(-1, -1), Coor(-1, 1)};
Piece::Path King::findPath(std::string const& start, std::string const& end)
{
    Coor const startCoor{start};
    Coor const endCoor{end};
    Path path{nullptr};
    if (abs(endCoor.x - startCoor.x) <= 1 &&
        abs(endCoor.y - startCoor.y) <= 1) {
        path = std::make_unique<std::vector<Coor>>();
    }
    return path;
}
std::vector<Coor> King::potentialEndPositions(std::string const& start)
{
    Coor const startCoor{start};
    std::vector<Coor> positions;
    // Note: if you are in check, you cannot castle,
    // so the potentialEnds don't include castle movement.
    for (auto const& direction : directions) {
        positions.emplace_back(direction + startCoor);
    }
    return positions;
}
/*--------------------------Pawn--------------------------*/
Piece::Path Pawn::findPath(std::string const& start, std::string const& end)
{
    Coor const startCoor{start};
    Coor const endCoor{end};
    Path path{nullptr};
    int advanceDirection = getColor() == Color::white ? 1 : -1;
    // Capture other piece.
    if (abs(endCoor.x - startCoor.x) == 1 &&
        endCoor.y - startCoor.y == advanceDirection) {
        {
            path = std::make_unique<std::vector<Coor>>();
        }
    }
    // Advance.
    else if (endCoor.x == startCoor.x) {
        if (endCoor.y - startCoor.y == advanceDirection) {
            path = std::make_unique<std::vector<Coor>>();
            path->emplace_back(
                endCoor); // Need to check if there is any piece at endCoor.
        }
        else if (endCoor.y - startCoor.y == 2 * advanceDirection &&
                 !hasMoved()) {
            path = std::make_unique<std::vector<Coor>>();
            path->emplace_back(startCoor.x, startCoor.y + advanceDirection);
            path->emplace_back(endCoor); // Need to check if there is any piece
                                         // in the path and at endCoor.
        }
    }
    return path;
}
std::vector<Coor> Pawn::potentialEndPositions(std::string const& start)
{
    Coor const startCoor{start};
    std::vector<Coor> positions;
    int advanceDirection = getColor() == Color::white ? 1 : -1;
    // Capture
    positions.emplace_back(startCoor.x + 1, startCoor.y + advanceDirection);
    positions.emplace_back(startCoor.x - 1, startCoor.y + advanceDirection);
    // Advance
    positions.emplace_back(startCoor.x, startCoor.y + advanceDirection);
    if (!hasMoved()) {
        positions.emplace_back(startCoor.x, startCoor.y + 2 * advanceDirection);
    }
    return positions;
}
/*--------------------------Knight--------------------------*/
std::vector<Coor> const Knight::directions = {
    Coor(1, 2),   Coor(2, 1),   Coor(2, -1), Coor(1, -2),
    Coor(-1, -2), Coor(-2, -1), Coor(-2, 1), Coor(-1, 2)};
Piece::Path Knight::findPath(std::string const& start, std::string const& end)
{
    Coor const endCoor{end};
    Path path{nullptr};
    auto positions = potentialEndPositions(start);
    auto it = std::find(positions.begin(), positions.end(), endCoor);
    if (it != positions.end()) {
        path = std::make_unique<std::vector<Coor>>();
    }
    return path;
}
std::vector<Coor> Knight::potentialEndPositions(std::string const& start)
{
    std::vector<Coor> positions;
    Coor const startCoor{start};
    for (auto const& direction : directions) {
        auto position = startCoor + direction;
        if (position.withInBoard()) {
            positions.emplace_back(position);
        }
    }
    return positions;
}

/*---------- Helper functions for Rook & Bishop ----------*/
// Assume a path exists, return the path (can be empty).
Piece::Path pathHelper(Coor const& startCoor, Coor const& endCoor)
{
    Piece::Path path = std::make_unique<std::vector<Coor>>();
    auto direction = findDirection(startCoor, endCoor);
    auto curCoor = startCoor + direction;
    while (curCoor != endCoor) {
        path->emplace_back(curCoor);
        curCoor += direction;
    }
    return path;
}
// Return all possible end positions.
std::vector<Coor> positionHelper(std::string const& start,
                                 std::vector<Coor> const& directions)
{
    std::vector<Coor> positions;
    Coor const startCoor{start};
    for (auto const& direction : directions) {
        auto curCoor = startCoor + direction;
        while (curCoor.withInBoard()) {
            positions.emplace_back(curCoor);
            curCoor += direction;
        }
    }
    return positions;
}
/*--------------------------Rook--------------------------*/
std::vector<Coor> const Rook::directions = {Coor(0, 1), Coor(1, 0), Coor(-1, 0),
                                            Coor(0, -1)};
Piece::Path Rook::findPath(std::string const& start, std::string const& end)
{
    Coor const startCoor{start};
    Coor const endCoor{end};
    // Rook cannot make this movement.
    if (startCoor.x != endCoor.x && startCoor.y != endCoor.y) {
        return nullptr;
    }
    return pathHelper(startCoor, endCoor);
}
std::vector<Coor> Rook::potentialEndPositions(std::string const& start)
{
    return positionHelper(start, directions);
}
/*--------------------------Bishop--------------------------*/
std::vector<Coor> const Bishop::directions = {Coor(1, 1), Coor(1, -1),
                                              Coor(-1, -1), Coor(-1, 1)};
Piece::Path Bishop::findPath(std::string const& start, std::string const& end)
{
    Coor const startCoor{start};
    Coor const endCoor{end};
    // Bishop cannot make this movement.
    if (abs(startCoor.x - endCoor.x) != abs(startCoor.y - endCoor.y)) {
        return nullptr;
    }
    return pathHelper(startCoor, endCoor);
}
std::vector<Coor> Bishop::potentialEndPositions(std::string const& start)
{
    return positionHelper(start, directions);
}
/*--------------------------Queen--------------------------*/
Piece::Path Queen::findPath(std::string const& start, std::string const& end)
{
    auto bPath = Bishop::findPath(start, end);
    if (bPath) {
        return bPath;
    }
    return Rook::findPath(start, end);
}
std::vector<Coor> Queen::potentialEndPositions(std::string const& start)
{
    auto positions = Bishop::potentialEndPositions(start);
    auto rookPositions = Rook::potentialEndPositions(start);
    positions.insert(positions.end(), rookPositions.begin(),
                     rookPositions.end());
    return positions;
}
