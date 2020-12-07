#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <iostream>
#include <unordered_map>
#include "../ChessBoard.h"

/* Record all pieces on board that has been moved. */
std::unordered_map<PieceType, std::vector<std::string>> findMovedPieces(Board const &board)
{
    // record piece that are moved and their current position.
    std::unordered_map<PieceType, std::vector<std::string>> movedPieces;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[Coor(i, j)] && board[Coor(i, j)]->hasMoved())
            {
                movedPieces[board[Coor(i, j)]->getPieceType()].emplace_back(Coor(i, j).str());
            }
        }
    }
    return movedPieces;
}

TEST_CASE("Display Setup")
{
    SECTION("Full board")
    {
        Board board;
        std::cout << board;
    }
    SECTION("Custom Setup")
    {
        Board board("../chessBoardConfig/onlyking.pos");
        REQUIRE(board["D1"]->getColor() == Color::white);
        REQUIRE(board["D1"]->getPieceType() == PieceType::king);
        REQUIRE(board["E1"] == nullptr);
        std::cout << board;
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
        // Bishop movement blocked
        REQUIRE(blackPlayer.submitMove(board, "C8", "A6") == InvalidMove::BLOCK);
        // Bishop invalid move
        REQUIRE(blackPlayer.submitMove(board, "C8", "B6") == InvalidMove::ILLEGAL_PIECE_MOVE);
        // Bishop move status false
        auto movedPieces = findMovedPieces(board);
        // should remain intact
        REQUIRE(movedPieces.size() == 0);
    }
}
TEST_CASE("Pawn")
{
    Player whitePlayer(Color::white);
    Player blackPlayer(Color::black);
    whitePlayer.getOpponent() = &blackPlayer;
    blackPlayer.getOpponent() = &whitePlayer;
    // full board
    Board board;
    SECTION("illegal movement")
    {
        // illegal diagnal move
        REQUIRE(blackPlayer.submitMove(board, "A7", "B6") == InvalidMove::ILLEGAL_PIECE_MOVE);
        // illegal move, a kight move
        REQUIRE(blackPlayer.submitMove(board, "H7", "G5") == InvalidMove::ILLEGAL_PIECE_MOVE);
        // no piece moved
        auto movedPieces = findMovedPieces(board);
        REQUIRE(movedPieces.size() == 0);
    }
    SECTION("move pawn")
    {
        // advance 1 then 2
        REQUIRE(blackPlayer.submitMove(board, "A7", "A6") == InvalidMove::NO_ERROR);
        REQUIRE(blackPlayer.submitMove(board, "A6", "A4") == InvalidMove::ILLEGAL_PIECE_MOVE);
        auto movedPieces = findMovedPieces(board);
        REQUIRE(movedPieces[PieceType::pawn].size() == 1);
        REQUIRE(find(movedPieces[PieceType::pawn].begin(), movedPieces[PieceType::pawn].end(), "A6") != movedPieces[PieceType::pawn].end());
    }
    SECTION("move multiple pawn")
    {
        REQUIRE(blackPlayer.submitMove(board, "B7", "B6") == InvalidMove::NO_ERROR);
        REQUIRE(blackPlayer.submitMove(board, "C7", "C5") == InvalidMove::NO_ERROR);
        REQUIRE(blackPlayer.submitMove(board, "H7", "H5") == InvalidMove::NO_ERROR);
        // backword move, illegal
        REQUIRE(blackPlayer.submitMove(board, "C5", "C6") == InvalidMove::ILLEGAL_PIECE_MOVE);
        auto movedPieces = findMovedPieces(board);
        REQUIRE(movedPieces[PieceType::pawn].size() == 3);
        std::cout << board;
    }
    SECTION("pawn block")
    {
        REQUIRE(blackPlayer.submitMove(board, "B7", "B5") == InvalidMove::NO_ERROR);
        REQUIRE(blackPlayer.submitMove(board, "B5", "B4") == InvalidMove::NO_ERROR);
        // blocked
        REQUIRE(whitePlayer.submitMove(board, "B2", "B4") == InvalidMove::BLOCK);
        REQUIRE(whitePlayer.submitMove(board, "C2", "C3") == InvalidMove::NO_ERROR);
        // capture
        REQUIRE(whitePlayer.submitMove(board, "C3", "B4") == InvalidMove::NO_ERROR);
        // after capture, only one moved piece is left on board.
        auto movedPieces = findMovedPieces(board);
        REQUIRE(movedPieces[PieceType::pawn].size() == 1);
        std::cout << board;
    }
}

TEST_CASE("castling")
{
    Player whitePlayer(Color::white);
    Player blackPlayer(Color::black);
    whitePlayer.getOpponent() = &blackPlayer;
    blackPlayer.getOpponent() = &whitePlayer;
    Board board("../chessBoardConfig/castle.pos");
    std::cout << board;
    // need to check by hand if it's a partial board.
    blackPlayer.checkStatus() = blackPlayer.isInCheck(board);
    whitePlayer.checkStatus() = whitePlayer.isInCheck(board);

    SECTION("check status")
    {
        REQUIRE(blackPlayer.checkStatus());
        REQUIRE_FALSE(whitePlayer.checkStatus());
    }
    SECTION("cannot castle: in check")
    {
        // long castle
        REQUIRE(blackPlayer.submitMove(board, "E8", "C8") == InvalidMove::INVALID_CASTLE);
        // short castle
        REQUIRE(blackPlayer.submitMove(board, "E8", "G8") == InvalidMove::INVALID_CASTLE);
    }
    SECTION("castle")
    {
        // long castle
        REQUIRE(whitePlayer.submitMove(board, "E1", "C1") == InvalidMove::NO_ERROR);
        auto movedPieces = findMovedPieces(board);
        REQUIRE(movedPieces[PieceType::rook].size() == 1);
        REQUIRE(movedPieces[PieceType::king].size() == 1);
    }
    SECTION("cannot castle: piece moved")
    {
        // castle
        REQUIRE(whitePlayer.submitMove(board, "E1", "G1") == InvalidMove::NO_ERROR);
        // move back
        REQUIRE(whitePlayer.submitMove(board, "F1", "F2") == InvalidMove::NO_ERROR);
        REQUIRE(whitePlayer.submitMove(board, "G1", "F1") == InvalidMove::NO_ERROR);
        REQUIRE(whitePlayer.submitMove(board, "F1", "E1") == InvalidMove::NO_ERROR);
        // try castle again
        REQUIRE(whitePlayer.submitMove(board, "E1", "C1") == InvalidMove::INVALID_CASTLE);
    }
}

TEST_CASE("castling under attach")
{
    Player whitePlayer(Color::white);
    Player blackPlayer(Color::black);
    whitePlayer.getOpponent() = &blackPlayer;
    blackPlayer.getOpponent() = &whitePlayer;
    Board board("../chessBoardConfig/castle.pos");
    SECTION("cannot castle: passing oppoent controled sqare")
    {
        whitePlayer.submitMove(board, "B5", "B6");
        // long castle, B8 is controlled by opponent
        REQUIRE(blackPlayer.submitMove(board, "E8", "C8") == InvalidMove::INVALID_CASTLE);
        // short castle, fine
        REQUIRE(blackPlayer.submitMove(board, "E8", "G8") == InvalidMove::NO_ERROR);
    }
}

TEST_CASE("checkmate")
{
    Player whitePlayer(Color::white);
    Player blackPlayer(Color::black);
    whitePlayer.getOpponent() = &blackPlayer;
    blackPlayer.getOpponent() = &whitePlayer;
    Board board("../chessBoardConfig/checkmate.pos");
    std::cout << board;
    SECTION("only check")
    {
        REQUIRE(whitePlayer.submitMove(board, "B5", "D7") == InvalidMove::NO_ERROR);
        REQUIRE(whitePlayer.submitMove(board, "H1", "F1") == InvalidMove::NO_ERROR);
        std::cout << board;
        REQUIRE(blackPlayer.checkStatus());
        REQUIRE_FALSE(blackPlayer.isInCheckMate(board));
        // now checkmate
        REQUIRE(whitePlayer.submitMove(board, "E1", "C1") == InvalidMove::NO_ERROR);
        std::cout << board;
        REQUIRE(blackPlayer.isInCheckMate(board));
    }
}