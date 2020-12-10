#ifndef MOVE_H
#define MOVE_H
#include "card.h"

enum class MoveType { Play, Discard, Rage, None };

class Move {
    MoveType movetype;
    Card card;
    public:
    Move();
    void setType(MoveType type);
    void setCard(Card c);
    MoveType getType();
    Card getCard();
};

#endif
