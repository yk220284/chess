#include <utility>
#include "util.hpp"
#include "board.hpp"
/* first being a x position, second being a y position. */

#pragma once
class Player
{
    Color color;
    bool inCheck = false;
    std::string kingPos = "";
    Player *opponent;
    /* Helper function determining if there is any piece in between.
    Smartly defines the word 'Between' according to the piece type at start position. */
    std::string const &locateKing(Board const &board);
    /* Helper functions checking if this move is a valid castle move. 
    Here we implement castling as a movement of the King! */
    bool isCastling(std::string const &start, std::string const &end);
    bool validateCastleMove(Board &board, std::string const &start, std::string const &end);
    /* Check if there is any opponent's piece that has a valid move to position coor. */
    bool underAttack(Board &board, Coor const &coor);

public:
    /* Set the color and the initial kingPos of this player accordingly. */
    Player(Color color);
    /* Do NOT free the opponent. */
    ~Player() = default;
    /* Do not copy player. */
    Player(Player const &) = delete;
    Player &operator=(Player const &) = delete;
    /* Get and set oppoent. */
    Player *const &getOpponent() const;
    Player *&getOpponent();
    /* Get and set check status. */
    bool const &checkStatus() const;
    bool &checkStatus();
    /* Get color. */
    Color const &getColor() const;
    /* Check the validity of the move without modifying the board, 
    return cooresponding error code. */
    InvalidMove validateMove(Board &board, std::string const &start, std::string const &end);
    /* Assume the move is valid and change the board and kingPos as appropriate. If not hypothetical, mark the piece as moved.
    Return a pointer to the captured piece if there is a capture otherwide nullptr.  */
    std::unique_ptr<Piece> makeMove(Board &board, std::string const &start, std::string const &end, bool hypothetical = true);
    /* Undo the makeMove by restoring the board. 
    Move the piece from end to start and put the captured piece back to end. */
    void moveBack(Board &board, std::string const &start, std::string const &end, std::unique_ptr<Piece> &capturedPiece);
    /* See if this player is in check.
    Used in
    1. validMove, check whether certain move will this player in check
    2. after makeMove, update wheter the opponent is in check. */
    bool isInCheck(Board &board);
    /* Check all possible move to see if the game has ended or not. */
    bool isInCheckMate(Board &board);
    /* Return true if valid move then make the change on board, else return false. */
    bool submitMove(Board &board, std::string const &start, std::string const &end);
};