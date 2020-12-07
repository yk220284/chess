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
        Board board(Board::DIR + "onlyking.pos");
        cout << board;
    }
}