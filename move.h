#ifndef MOVE_H
#define MOVE_H
#include "card.h"

enum class MoveType { Play, Discard };

class Move {
    MoveType movetype;
    Card card;
    public:
    Move(MoveType type, Card card);
};

#endif
