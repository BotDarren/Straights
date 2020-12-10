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
    Deck deck;
    // Holds the top score currently, will be recalculated at the end of each round
    int topscore;
    // Holds a vector of the 4 players
    std::vector<Player> players;
    // Holds the round number
    int roundnum;
    // Holds the current seed of the deck
    int seed;
    // Holds whether this is the first play of the round: default of true, will be changed
    bool firstPlay = true;
    // Stores the cards on the board
    std::vector<Card> cards;
    // Which player is playing right now
    int curplayer;
public:
    // Constructor with the given seed
    Board(int seed);
    // Adds a player of the given type
    void addPlayer(PlayerType type);
    // Sets the player to begin
    void setStart();
    // Makes the current player make a move: play a card or discard
    void makeMove();
    // Deals the card
    void dealCard();
    // Starts the game
    void start();
    // Prints the deck
    void printDeck();
    // Returns the top card
    Card topCard();
    // Gets the players score
    int getPlayerScore(int index);
    // Returns whether or not the round is over
    bool roundOver();
    // Returns whether or not the game is over
    bool gameOver();
    // Returns whether or the current move is the first
    bool firstMove();
    // Returns the winners: assuming the game is over
    std::vector<int> getWinners();
};

#endif
