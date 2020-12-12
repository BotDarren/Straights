#ifndef BOARD_H
#define BOARD_H
#include "subject.h"
#include "deck.h"
#include "card.h"
#include "player.h"
#include "controller.h"
#include <vector>
#include <memory>

// This enum is used when the notify method of the board is called
// The view will fetch this state from the board and be able to decide what to do
enum class State { NEEDPLAYER, NEWROUND, PRINTCARD, RAGEQUIT }

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
    bool firstplay = true;
    // Stores the cards on the board
    std::vector<std::shared_ptr<Card>> cards;
    // Which player is playing right now
    int curplayer;
    // Stores the current state of the board: this is used by the view
    State curstate;
public:
    // Constructor without a given seed: this will initialize the deck 
    // with a seed based on the system time
    Board();
    // Constructor with the given seed
    Board(int seed);
    // Changes the seed of the game
    void setSeed(int s);
    // Adds a player of the given type
    void addPlayer(PlayerType type);
    // Sets the player to begin
    void setStart();
    // Makes the current player rage quit
    void rage();
    // Makes the current player make a move: this is used for a computer
    void makeMove();
    // Makes the current player make a move: this is used for a player
    void makeMove(Card c = Card(Ace,Spade));
    // Deals the card
    void dealCard();
    // Starts the game
    void start();
    // Goes to the next round
    void nextRound();
    // Prints the deck
    void printDeck();
    // Returns the top card
    std::shared_ptr<Card> topCard();
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
