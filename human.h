#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"
#include "move.h"

class Human : public Player {
public:
    // Constructs a human player
    Human(Board *model);
    // Makes a move: this can either be playing a card or discarding a card
    Move play(Card c, bool mtype) override;
    // Returns the type of player: Human
    PlayerType getType();
};

#endif
