#ifndef MOVE_H
#define MOVE_H
#include "card.h"

// Stores the types of moves
enum class MoveType { Play, Discard, None };

class Move {
    // Stores the type of move
    MoveType movetype;
    // Stores the card that we are doing the move on
    Card card;
    public:
    // Default constructor for a move. Constructs with movetype None.
    Move();
    // Sets the type of move
    void setType(MoveType type);
    // Sets the card that the move is on
    void setCard(Card c);
    // Returns the type of move
    MoveType getType() const;
    // Returns the card the move is on
    Card getCard() const;
};

#endif
