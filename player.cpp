#include "player.hpp"
#include "util.hpp"
#include <algorithm>
#include <utility>

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
/* ----validate Castling---- */
bool Player::isCastling(std::string const &start, std::string const &end)
{
    if (color == Color::black)
    {
        return start == "E8" && (end == "C8" || end == "G8");
    }
    else
    {
        return start == "E1" && (end == "C1" || end == "G1");
    }
}
/* Given the castle movement of the king, return the start and end location of the cooresponding rook. */
std::pair<Coor, Coor> locateRook(std::string const &kingStart, std::string const &kingEnd)
{
    Coor const kingStartCoor{kingStart};
    Coor const kingEndCoor{kingEnd};
    // short castle is the one that king exchange with the rhs castle.
    bool const isShortCastle = kingStartCoor.x < kingEndCoor.x;
    // direction of movement of the King.
    Coor const direction = findDirection(kingStartCoor, kingEndCoor);
    // distance between king and castle
    int const distance = isShortCastle ? 2 : 3;
    // locate rook to castle.
    Coor rookStartCoor = kingStartCoor;
    for (int i = 0; i <= distance; i++)
    {
        rookStartCoor += direction;
    }
    Coor rookEndCoor = kingStartCoor + direction;
    return std::make_pair(rookStartCoor, rookEndCoor);
}
bool Player::validateCastleMove(Board &board, std::string const &start, std::string const &end)
{
    // 1. cannot be in check
    if (inCheck)
    {
        return false;
    }
    // 2. king or rook has moved
    auto p = locateRook(start, end);
    Coor const kingStartCoor{start};
    Coor const kingEndCoor{end};
    auto const &rookStartCoor = p.first;
    // locate two pieces.
    auto const &king = board[kingStartCoor];
    auto const &rook = board[rookStartCoor];
    if (!king || !rook || king->hasMoved() || rook->hasMoved())
    {
        return false;
    }
    // 3. block or under attack
    auto midCoor = kingStartCoor;
    // distance is the number of sqare between two pieces.
    auto distance = abs(rookStartCoor.x - kingStartCoor.x) - 1;
    auto direction = findDirection(kingStartCoor, kingEndCoor);
    for (int i = 0; i < distance; i++)
    {
        midCoor += direction;
        if (board[midCoor])
        {
            // blocked
            return false;
        }
        if (i < 2 && underAttack(board, midCoor))
        {
            // movement of king involve squares under attack.
            return false;
        }
    }
    return true;
    // 4. make move see if in check. Not possible.
    // auto kingCapture = makeMove(board, start, end);
    // auto rookCapture = makeMove(board, rookStartCoor.str(), rookEndCoor.str());
    // bool inCheck = isInCheck(board);
    // moveBack(board, rookStartCoor.str(), rookEndCoor.str(), rookCapture);
    // moveBack(board, start, end, kingCapture);
    // return !inCheck;
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
    // 5a. check if it is a castling move, before checking standard move.
    if (isCastling(start, end))
    {
        if (validateCastleMove(board, start, end))
        {
            return InvalidMove::NO_ERROR;
        }
        else
        {
            return InvalidMove::INVALID_CASTLE;
        }
    }
    // 5b. check for valid standard move.
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
    /* ---- Make a hypothetical move to test if that's valid. ---- */
    auto capturedPiece = makeMove(board, start, end);
    // 7. the piece at the destination is your own piece.
    if (capturedPiece && (capturedPiece->getColor() == color))
    {
        moveBack(board, start, end, capturedPiece); // Undo the damage.
        return InvalidMove::CAPTURE_OWN;
    }
    // 5c. Moved Pawn diagnally without capturing any piece.
    if (!capturedPiece && path->size() == 0 && board[end]->getPieceType() == PieceType::pawn)
    {
        moveBack(board, start, end, capturedPiece); // Undo the damage.
        return InvalidMove::ILLEGAL_PIECE_MOVE;
    }
    // 8a. Captured opponent's king, don't need to check whether I am in check anymore.
    if (capturedPiece && capturedPiece->getPieceType() == PieceType::king)
    {
        moveBack(board, start, end, capturedPiece); // Undo the damage.
        return InvalidMove::NO_ERROR;
    }
    // 8b. your move results in being in check yourself.
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
void printError(InvalidMove invalidMove, Board const &board, std::string const &start, std::string const end)
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
        std::cerr << board[start]->getColor() << "'s " << board[start]->getPieceType()
                  << " cannot move from " << start << " to " << end
                  << " as there is a piece blocking in the middle!\n";
        break;
    case InvalidMove::CAPTURE_OWN:
        std::cerr << "Try to capture a " << board[end]->getColor() << ' '
                  << board[end]->getPieceType() << " (your own) piece\n";
        break;
    case InvalidMove::SELF_IN_CHECK:
        std::cerr << "This move results you in check, hence not valid.\n";
        break;
    case InvalidMove::INVALID_CASTLE:
        std::cerr << "This is an invalid castling.\n";
        break;
    }
}
/* ----submitMove---- */
InvalidMove Player::submitMove(Board &board, std::string const &start, std::string const &end)
{
    auto err_code = validateMove(board, start, end);
    if (err_code == InvalidMove::NO_ERROR)
    {
        // After a valid move, I cannot be in check.
        inCheck = false;
        std::cout << color << "'s " << board[start]->getPieceType() << " moves from "
                  << start << " to " << end;
        auto capturedPiece = makeMove(board, start, end, false);
        if (capturedPiece)
        {
            std::cout << " taking " << capturedPiece->getColor() << "'s " << capturedPiece->getPieceType();
        }
        std::cout << std::endl;
        // check if it's a castling move, if so, move the cooresponding Rook.
        if (isCastling(start, end))
        {
            auto p = locateRook(start, end);
            auto const &rookStartCoor = p.first;
            auto const &rookEndCoor = p.second;
            std::cout << color << "'s " << board[rookStartCoor]->getPieceType() << " moves from "
                      << rookStartCoor << " to " << rookEndCoor
                      << " finish castling.\n";
            makeMove(board, rookStartCoor.str(), rookEndCoor.str(), false);
        }
        if (opponent->isInCheck(board))
        {
            // Opponent in check.
            opponent->checkStatus() = true;
            if (opponent->isInCheckMate(board))
            {
                // Won the game.
                std::cout << opponent->getColor() << " is in checkmate\n";
            }
            else
            {
                // opponents still has some valid moves.
                std::cout << opponent->getColor() << " is in check\n";
            }
        }
    }
    else
    {
        printError(err_code, board, start, end);
    }
    return err_code;
}
/* ----makeMove---- */
std::unique_ptr<Piece> Player::makeMove(Board &board, std::string const &start, std::string const &end, bool hypothetical)
{
    if (!hypothetical)
    {
        board[start]->markMoved();
    }
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
/* ---- Under attack ---- */
bool Player::underAttack(Board &board, Coor const &coor) const
{
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if (board[Coor(x, y)] &&
                // There is at least one opponent's piece
                board[Coor(x, y)]->getColor() != color &&
                // has a valid move from its position to position coor.
                opponent->validateMove(board, Coor(x, y).str(), coor.str()) == InvalidMove::NO_ERROR)
            {
                return true;
            }
        }
    }
    return false;
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
    return underAttack(board, Coor(kingPos));
}

bool Player::isInCheckMate(Board &board)
{
    if (!inCheck)
    {
        return false;
    }
    // Try all movements of all my pieces see if there is at least 1 valid move.
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            auto const &piece = board[Coor(x, y)];
            if (piece && piece->getColor() == color)
            {
                auto potentialEnds = piece->potentialEndPositions(Coor(x, y).str());
                for (auto const &end : potentialEnds)
                {
                    // Exists at least 1 valid move for me.
                    if (validateMove(board, Coor(x, y).str(), end.str()) == InvalidMove::NO_ERROR)
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
