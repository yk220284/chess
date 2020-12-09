#include "ChessBoard.h"
ChessBoard::ChessBoard()
{
    whitePlayer = new Player(Color::white);
    blackPlayer = new Player(Color::black);
    whitePlayer->getOpponent() = blackPlayer;
    blackPlayer->getOpponent() = whitePlayer;
    resetBoard();
}
ChessBoard::ChessBoard(std::string const& config_file) : ChessBoard()
{
    board.setBoard(config_file);
}
ChessBoard::~ChessBoard()
{
    delete whitePlayer;
    delete blackPlayer;
}
void ChessBoard::resetBoard()
{
    std::cout << "A new chess game is started!\n";
    whiteTurn = true;
    board.setBoard();
}
void ChessBoard::submitMove(std::string const& start, std::string const& end)
{
    if (whiteTurn) {
        // If whitePlayer managed to submitMove, next turn is black player,
        // else, next turn is still whitePlayer.
        whiteTurn = (whitePlayer->submitMove(board, start, end) !=
                     InvalidMove::NO_ERROR);
    }
    else {
        whiteTurn = (blackPlayer->submitMove(board, start, end) ==
                     InvalidMove::NO_ERROR);
    }
}