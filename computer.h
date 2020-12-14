#ifndef COMPUTER_H
#define COMPUTER_H
#include "player.h"
#include "move.h"

class Computer : public Player {
public:
    // Constructs a computer player
    Computer(Board *model);
    // Makes a move: this can either be playing a card or discarding a card
    Move play(Card c, bool mtype) override;
    // Returns the type of player: Computer
    PlayerType getType() const override;
};

#endif
