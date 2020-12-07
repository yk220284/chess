/* ChessBoard is the interface of the GAME, rather than just a board.*/
#pragma once
#include "player.hpp"
#include "board.hpp"
#include "util.hpp"

class ChessBoard
{
    Board board;
    Player *whitePlayer;
    Player *blackPlayer;
    bool whiteTurn = true;

public:
    /* set up a standard board. */
    ChessBoard();
    /* use config_file to construct board. */
    ChessBoard(std::string const &config_file);
    /* Do not copy ChessBoard(Game). */
    ChessBoard(ChessBoard const &) = delete;
    ~ChessBoard();
    ChessBoard &operator=(ChessBoard const &) = delete;
    void resetBoard();
    void submitMove(std::string const &start, std::string const &end);
};