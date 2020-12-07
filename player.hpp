#include <utility>
#include "util.hpp"
#include "board.hpp"
/* first being a x position, second being a y position. */

#pragma once
class Player
{
    Color color;
    bool inCheck = false;
    Player *opponent;
    /* a string represents the position of the player's King. 
     * assigned later when 
     * 1. king has moved
     * 2. checking if the player is in check. */
    std::string kingPos = "";
    /* locate the position of king if kingPos is empty. */
    std::string const &locateKing(Board const &board);
    /* Helper functions checking if this move is a valid castle move. 
    Here we implement castling as a movement of the King! */
    bool isCastling(std::string const &start, std::string const &end);
    /* validate if this castle violates any rules. */
    bool validateCastleMove(Board &board, std::string const &start, std::string const &end);
    /* Check if there is any opponent's piece that has a valid move to position coor. */
    bool underAttack(Board &board, Coor const &coor) const;
    /* Check the validity of the move without modifying the board, 
     * return cooresponding error code. */
    InvalidMove validateMove(Board &board, std::string const &start, std::string const &end);
    /* Assume the move is valid and change the board and kingPos as appropriate. If not hypothetical, mark the piece as moved.
     * Return a pointer to the captured piece if there is a capture otherwide nullptr.  */
    std::unique_ptr<Piece> makeMove(Board &board, std::string const &start, std::string const &end, bool hypothetical = true);
    /* Undo the makeMove by restoring the board. 
     * Move the piece from end to start and put the captured piece back to end. */
    void moveBack(Board &board, std::string const &start, std::string const &end, std::unique_ptr<Piece> &capturedPiece);

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
    /* Return InvalidMove::NO_ERROR if valid move then make the change on board, else return the err_code. */
    InvalidMove submitMove(Board &board, std::string const &start, std::string const &end);
    /* See if this player is in check.
     * If King pos unknown, update King pos.
     * Used in
     * 1. validateMove, check whether certain move will this player in check
     * 2. after makeMove, update wheter the opponent is in check. */
    bool isInCheck(Board &board);
    /* Check if a valid move exists to see if the game has ended or not. */
    bool isInCheckMate(Board &board);
};