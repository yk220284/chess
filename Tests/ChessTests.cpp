#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../ChessBoard.h"
#include <iostream>
using namespace std;

TEST_CASE("Display Setup")
{
    SECTION("Full board")
    {
        Board board;
        cout << board;
    }
    SECTION("Custom Setup")
    {
        Board board("../chessBoardConfig/onlyking.pos");
        REQUIRE(board["D1"]->getColor() == Color::white);
        REQUIRE(board["D1"]->getPieceType() == PieceType::king);
        REQUIRE(board["E1"] == nullptr);
        cout << board;
    }
}
TEST_CASE("Players")
{
    Player whitePlayer(Color::white);
    Player blackPlayer(Color::black);
    whitePlayer.getOpponent() = &blackPlayer;
    blackPlayer.getOpponent() = &whitePlayer;
    SECTION("Opponent")
    {
        REQUIRE(whitePlayer.getOpponent()->getColor() == Color::black);
        REQUIRE(blackPlayer.getOpponent()->getColor() == Color::white);
    }
    SECTION("invalid positions")
    {
        // full board
        Board board;
        // white player move black piece
        REQUIRE(whitePlayer.submitMove(board, "D7", "D5") == InvalidMove::OPPONENT_PIECE);
        // invalid position
        REQUIRE(whitePlayer.submitMove(board, "@&", "D5") == InvalidMove::INVALID_POS);
        REQUIRE(whitePlayer.submitMove(board, "S9", "D5") == InvalidMove::INVALID_POS);
        REQUIRE(whitePlayer.submitMove(board, "A9", "D5") == InvalidMove::INVALID_POS);
        // empty square
        REQUIRE(whitePlayer.submitMove(board, "G3", "D5") == InvalidMove::NO_PIECE);
        // stationary move
        REQUIRE(whitePlayer.submitMove(board, "D2", "D2") == InvalidMove::STATIONARY_MOVE);
    }
}
