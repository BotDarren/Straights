#ifndef COMPUTER_H
#define COMPUTER_H
#include "player.h"
#include "move.h"

class Computer : public Player {
public:
    // Constructs a human player
    Computer();
    // Makes a move: this can either be playing a card or discarding a card
    Move play() override;
};

#endif
