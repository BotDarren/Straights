#ifndef BOARD_H
#define BOARD_H
#include "subject.h"
#include "deck.h"
#include "card.h"
#include "player.h"
#include "controller.h"
#include <vector>
#include <memory>

class Board : public Subject {
    // Holds the current deck
    std::shared_ptr<Deck> deck;
    // Holds the top score currently, will be recalculated at the end of each round
    int topscore;
    // Holds a vector of the 4 players
    std::vector<std::shared_ptr<Player>> players;
    // Holds the round number
    int roundnum;
    // Holds the current seed of the deck
    int seed;
    // Holds whether this is the first play of the round: default of true, will be changed
    bool firstPlay = true;
    // Stores the cards on the board
    std::vector<std::shared_ptr<Card>> cards;
    // Which player is playing right now
    int curplayer;
public:
    // Constructor with the given seed
    Board(int seed);
    // Sets the player to begin
    void setStart();
    // Plays the provided card
    void playCard();
    // Deals the card
    void dealCard();
    // Starts the game
    void start();
    // Prints the deck
    void printDeck();
    // Gets the players score
    void getPlayerScore(int index);
    // Returns whether or not the round is over
    bool roundOver();
    // Returns whether or not the game is over
    bool gameOver();
    // Returns the winners: assuming the game is over
    std::vector<int> getWinners();
};

#endif
