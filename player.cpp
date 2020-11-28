#include "player.hpp"
#include <algorithm>

Player::Player(Color color) : color(color) {}
Player *Player::getOpponent() const
{
    return opponent;
}

/* ----validMove---- */
// bool Player::pieceInBetween(Board const &board, std::string const &start, std::string const &end) const
// {
//     auto const &startPiece = board[start];
//     return true;
// }
bool Player::validMove(Board &board, std::string const &start, std::string const &end) const
{
    auto const &startPiece = board[start];
    auto const &capturedPiece = board[end];
    if (!startPiece)
    {
        std::cerr << "There is no piece at position " << start << "!\n";
        return false;
    }
    if (startPiece->getColor() != color)
    {
        std::cerr << "It is not " << startPiece->getColor() << "’s turn to move!\n";
        return false;
    }
    if (capturedPiece && (capturedPiece->getColor() == color))
    {
        std::cerr << "Try to capture a " << capturedPiece->getColor() << " (your own) piece.\n";
        return false;
    }
    auto path = startPiece->findPath(start, end);
    if (!path)
    {
        // not a valid move for this piece.
        return false;
    }
    // BELOW UNTESTED! TEST AFTER IMPLEMENTING findPath()!.
    auto occupiedPos = std::find_if(path->begin(), path->end(), [&board](auto const &pos) {
        return board[pos];
    });
    if (occupiedPos != path->end())
    {
        std::cerr << "There is a piece at position " << *occupiedPos << " cannot jump!\n";
        return false;
    }
    // auto capturedPiece = makeMove(board, start, end); test if this will result in check.
}
/* ----submitMove---- */
bool Player::submitMove(Board &board, std::string const &start, std::string const end)
{
    if (validMove(board, start, end))
    {
        auto capturedPiece = makeMove(board, start, end);
        // TODO: output capture. if not null...
        opponent->updateCheck(board);
        // TODO: output if in check, ideally within the updateCheck();
        return true;
    }
    return false;
}
/* ----makeMove---- */
std::unique_ptr<Piece> Player::makeMove(Board &board, std::string const &start, std::string const &end) const
{
}
/* ----update check status---- */
bool Player::updateCheck(Board const &board) {}