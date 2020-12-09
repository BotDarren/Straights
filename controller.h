#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "board.h"
#include "player.h"
#include "deck.h"

class Controller {
    // Pointer to the view
    Board model;
    // Pointer to the current deck
    std::shared_ptr<Deck> curdeck;
    // Vector of the current players
    std::vector<Player> curplayers;
    int curseed;
public:
    Controller( Board* model );
    // Shuffles the current deck
    void shuffle( std::shared_ptr<Deck> deck );
    // Happens when a player chooses to rage quit: the human is replaced with a computer
    std::shared_ptr<Player> RageQuit( Player &player );
    // Prints the current deck of the player: 13 cards per line (not part of official game)
    void printDeck( Player &player );
    // Makes the given player make a move: this can either be a human/computer type of move
    void makeMove( Player &player );
    // Sets the seed for the shuffling
    void setSeed( int seed );
    // Begins a new round: when called when the round should have ended, will inform the view
    void newRound();
};

#endif
