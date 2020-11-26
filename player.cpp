#include "player.hpp"

Player::Player(Color color) : color(color) {}
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