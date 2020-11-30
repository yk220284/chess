#include <iostream>
#include "board.hpp"
#include "player.hpp"
#include "util.hpp"
using namespace std;

int main()
{
    Player whitePlayer(Color::white);
    Player blackPlayer(Color::black);
    whitePlayer.getOpponent() = &blackPlayer;
    blackPlayer.getOpponent() = &whitePlayer;

    /* ----Test Piece---- */
    Board bd2(filenames::TEST_ROOK);
    cout << bd2;
    whitePlayer.submitMove(bd2, "A1", "A9");
    whitePlayer.submitMove(bd2, "A1", "A3");
    whitePlayer.submitMove(bd2, "A1", "B2");
    whitePlayer.submitMove(bd2, "A1asdfsdf", "B2");
    whitePlayer.submitMove(bd2, "E9", "B2");
    whitePlayer.submitMove(bd2, "A1", "A4");
    /* ----Test In check---- */
    Board bd3(filenames::IN_CHECK);
    cout << bd3;
    whitePlayer.submitMove(bd3, "A2", "B2");
}
