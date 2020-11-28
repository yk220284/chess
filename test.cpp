#include <iostream>
#include "board.hpp"
#include "player.hpp"
#include "util.hpp"
using namespace std;

int main()
{
    /* ----Test Board----*/
    Board bd(filenames::DEFALT_CONFIG);
    Board bd1(filenames::ONLY_KING);
    cout << bd;
    cout << bd1;

    // cout << bd1;
    /* ----Test Player----*/
    Player whitePlayer(Color::white);
    whitePlayer.validMove(bd1, "A1", "A2"); // No piece at E2.
    whitePlayer.validMove(bd1, "E8", "E3"); // try to move a black piece.
    whitePlayer.validMove(bd1, "E1", "E2"); // try to capture own piece.
    whitePlayer.validMove(bd1, "E1", "E8"); // crazy move.
}
