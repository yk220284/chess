#pragma once
#include <utility>
#include "util.hpp"
#include "board.hpp"
/* first being a x position, second being a y position. */

class Player
{
    Color color;
    bool inCheck = false;
    std::string kingPos;

public:
    Player *opponent;
    /* Set the color and the initial kingPos of this player accordingly. */
    Player(Color color);
    /* Do NOT free the opponent. */
    ~Player() = default;
    /* Do not copy player. */
    Player(Player const &) = delete;
    Player &operator=(Player const &) = delete;
    /* Check the validity of the move without modifying the board. */
    bool validMove(Board const &board, std::string const &start, std::string const &end) const;
    /* Assume the move is valid and change the board and kingPos as appropriate.
    Return a pointer to the captured piece if there is a capture otherwide nullptr.  */
    std::unique_ptr<Piece> makeMove(Board &board, std::string const &start, std::string const &end) const;
    /* See if this player is in check, and update member variable inCheck.
    Then return member variable inCheck. Used in
    1. validMove, check whether certain move will this player in check
    2. after makeMove, update wheter the opponent is in check. */
    bool updateCheck(Board const &board);
    /* Return true if valid move then make the change on board, else return false. */
    bool submitMove(Board &board, std::string const &start, std::string const end);
};