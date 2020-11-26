#include "ChessBoard.h"
ChessBoard::ChessBoard()
{
    whitePlayer = new Player(Color::white);
    blackPlayer = new Player(Color::black);
    whitePlayer->opponent = blackPlayer;
    blackPlayer->opponent = whitePlayer;
    board = new Board(); // Use the defult file to set board.
}
ChessBoard::ChessBoard(std::string const &config_file) : ChessBoard()
{
    board->setBoard(config_file);
}

ChessBoard::~ChessBoard()
{
    delete whitePlayer;
    delete blackPlayer;
    delete board;
}
void ChessBoard::resetBoard()
{
    board->setBoard();
}
void ChessBoard::submitMove(std::string const &start, std::string const &end)
{
    if (whiteTurn)
    {
        // If whitePlayer managed to submitMove, next turn is black player,
        // else, next turn is still whitePlayer.
        whiteTurn = !(whitePlayer->submitMove(*board, start, end));
    }
    else
    {
        whiteTurn = blackPlayer->submitMove(*board, start, end);
    }
}