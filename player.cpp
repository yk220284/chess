#include "player.hpp"
#include <algorithm>

Player::Player(Color color) : color(color) {}
Player *&Player::getOpponent()
{
    return opponent;
}
Player *const &Player::getOpponent() const
{
    return opponent;
}
bool const &Player::checkStatus() const
{
    return inCheck;
}
bool &Player::checkStatus()
{
    return inCheck;
}
Color const &Player::getColor() const
{
    return color;
}
/* ----validateMove---- */
InvalidMove Player::validateMove(Board &board, std::string const &start, std::string const &end)
{
    // 1. not valid position string.
    if (!(validPosStr(start) && validPosStr(end)))
    {
        return InvalidMove::INVALID_POS;
    }
    // 2. no piece at starting position.
    auto const &startPiece = board[start];
    if (!startPiece)
    {
        return InvalidMove::NO_PIECE;
    }
    // 3. piece at starting position is not yours.
    if (startPiece->getColor() != color)
    {

        return InvalidMove::OPPONENT_PIECE;
    }
    // 4. didn't move the piece.
    if (start == end)
    {
        return InvalidMove::STATIONARY_MOVE;
    }
    // 5. this is not a valid move for this piece.
    auto path = startPiece->findPath(start, end);
    if (!path)
    {
        return InvalidMove::ILLEGAL_PIECE_MOVE;
    }
    // 6. there is a piece blocking the move.
    auto occupiedPos = std::find_if(path->begin(), path->end(), [&board](auto const &pos) {
        return (board[pos] != nullptr);
    });
    if (occupiedPos != path->end())
    {
        return InvalidMove::BLOCK;
    }
    // 7. the piece at the destination is your own piece.
    // Make a hypothetical move to test if that's valid.
    auto capturedPiece = makeMove(board, start, end);
    if (capturedPiece && (capturedPiece->getColor() == color))
    {
        moveBack(board, start, end, capturedPiece); // Undo the damage.
        return InvalidMove::CAPTURE_OWN;
    }
    // 8. your move results in being in check yourself.
    // Captured opponent's king, don't need to check whether I am in check anymore.
    if (capturedPiece && capturedPiece->getPieceType() == PieceType::king)
    {
        moveBack(board, start, end, capturedPiece); // Undo the damage.
        return InvalidMove::NO_ERROR;
    }
    if (isInCheck(board))
    {
        moveBack(board, start, end, capturedPiece); // Undo the damage.
        return InvalidMove::SELF_IN_CHECK;
    }
    // 0. no error :-)
    moveBack(board, start, end, capturedPiece);
    return InvalidMove::NO_ERROR;
}
/* ---- print error message ---- */
void printError(InvalidMove invalidMove, Board const &board, std::string const &start, std::string const end, std::ostream &out = std::cout)
{
    switch (invalidMove)
    {
    case InvalidMove::NO_ERROR:
        break;
    case InvalidMove::INVALID_POS:
        std::cerr << start << " or " << end << " is not a valid position on board\n";
        break;
    case InvalidMove::NO_PIECE:
        std::cerr << "There is no piece at position " << start << "!\n";
        break;
    case InvalidMove::OPPONENT_PIECE:
        std::cerr << "It is not " << board[start]->getColor() << "’s turn to move!\n";
        break;
    case InvalidMove::STATIONARY_MOVE:
        std::cerr << "You didn't move your piece (the start position is the same as the end position).\n";
        break;
    case InvalidMove::ILLEGAL_PIECE_MOVE:
        std::cerr << "From " << start << " to " << end
                  << " is not a valid move for " << board[start]->getPieceType()
                  << std::endl;
        break;
    case InvalidMove::BLOCK:
        std::cerr << "There is a piece blocking the move from " << start << " to " << end << "!\n";
        break;
    case InvalidMove::CAPTURE_OWN:
        std::cerr << "Try to capture a " << board[end]->getColor() << ' '
                  << board[end]->getPieceType() << " (your own) piece\n";
        break;
    case InvalidMove::SELF_IN_CHECK:
        std::cerr << "This move results you in check, hence not valid.\n";
        break;
    }
}
/* ----submitMove---- */
bool Player::submitMove(Board &board, std::string const &start, std::string const end)
{
    auto err_code = validateMove(board, start, end);
    if (err_code == InvalidMove::NO_ERROR)
    {
        auto capturedPiece = makeMove(board, start, end);
        if (opponent->isInCheck(board))
        {
            opponent->checkStatus() = true;
            if (opponent->isInCheckMate(board))
            {
                // Won the game.
                std::cout << opponent->getColor() << " is in checkmate\n";
            }
        }
        return true;
    }
    else
    {
        printError(err_code, board, start, end);
        return false;
    }
}
/* ----makeMove---- */
std::unique_ptr<Piece> Player::makeMove(Board &board, std::string const &start, std::string const &end)
{
    // Tracking our king's position.
    if (board[start]->getPieceType() == PieceType::king)
    {
        kingPos = end;
    }
    auto capturedPiece = std::move(board[end]);
    board[end] = std::move(board[start]);
    return capturedPiece;
}
/* ----moveBack---- */
void Player::moveBack(Board &board, std::string const &start, std::string const &end, std::unique_ptr<Piece> &capturedPiece)
{
    // Tracking our king's position.
    if (board[end]->getPieceType() == PieceType::king)
    {
        kingPos = start;
    }
    board[start] = std::move(board[end]);
    board[end] = std::move(capturedPiece);
}
/* ----update check status---- */
std::string const &Player::locateKing(Board const &board)
{
    if (kingPos.empty())
    {
        for (int x = 0; x < 8; x++)
        {
            for (int y = 0; y < 8; y++)
            {
                if (board[Coor(x, y)] &&
                    (board[Coor(x, y)]->getPieceType() == PieceType::king) &&
                    (board[Coor(x, y)]->getColor() == color))
                {
                    kingPos = Coor(x, y).str();
                    return kingPos;
                }
            }
        }
    }
    return kingPos;
}
bool Player::isInCheck(Board &board)
{
    auto const &kingPos = locateKing(board);
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if (board[Coor(x, y)] &&
                // Opponent's piece.
                board[Coor(x, y)]->getColor() != color &&
                // Exists a valid move from their piece to my king.
                opponent->validateMove(board, Coor(x, y).str(), kingPos) == InvalidMove::NO_ERROR)
            {
                return true;
            }
        }
    }
    return false;
}

bool Player::isInCheckMate(Board &board)
{
    // UNTESTED!!!!!!!
    if (!inCheck)
    {
        return false;
    }
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            auto const &piece = board[Coor(x, y)];
            if (piece)
            {
                auto potentialEnds = piece->potentialEndPositions(Coor(x, y).str());
                auto it = std::find_if(potentialEnds.begin(), potentialEnds.end(), [&](Coor const &end) {
                    InvalidMove err_code = validateMove(board, Coor(x, y).str(), end.str());
                    return err_code == InvalidMove::NO_ERROR;
                });
                if (it != potentialEnds.end())
                {
                    return false;
                }
            }
        }
    }
    return true;
}