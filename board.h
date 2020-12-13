#ifndef BOARD_H
#define BOARD_H
#include "subject.h"
#include "deck.h"
#include "card.h"
#include "player.h"
#include "controller.h"
#include <vector>
#include <memory>

struct ArgExn {
    std::string message; // details of the problem    
    ArgExn( std::string message );
}; 
// This enum is used when the notify method of the board is called
// The view will fetch this state from the board and be able to decide what to do
enum class State { NEWROUND, PRINTCARD, RAGEQUIT, 
                    PLAY, DISCARD, ENDROUND, ENDGAME };

class Board : public Subject {
    // Holds the current deck
    std::shared_ptr<Deck> deck;
    // Holds a vector of the 4 players
    std::vector<std::shared_ptr<Player>> players;
    // Holds the round number
    int roundnum;
    // Holds whether this is the first play of the round: default of true, will be changed
    bool firstplay = true;
    // Stores the cards on the board
    std::vector<std::shared_ptr<Card>> cards;
    // Which player is playing right now
    int curplayer;
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
    // Makes the current player make a move: the given card will be a default card for a computer
    // And the computer subclass will not be using the card c
    void makeMove(Card c, bool mtype);
    // Deals the card
    void dealCard();
    // Returns the index of the current player
    int getCurrentPlayer();
    // Returns the deck of the game
    std::vector<std::shared_ptr<Card>> getDeck();
    // Returns the cards that have been played
    std::vector<std::shared_ptr<Card>> getPlayed();
    // Returns the hand of the current player
    std::vector<std::shared_ptr<Card>> getHand();
    // Returns the discard pile of the current player
    std::vector<std::shared_ptr<Card>> getDiscard();
    // Returns the valid plays of the current player
    std::vector<std::shared_ptr<Card>> getValidPlays();
    // Returns the current players
    std::vector<std::shared_ptr<Player>> getPlayers();
    // Returns the type of the current player
    PlayerType getPlayerType();
    // Starts the game
    void start();
    // Goes to the next round
    void nextRound();
    // Returns the top card
    std::shared_ptr<Card> topCard();
    // Returns the most recently discarded card
    std::shared_ptr<Card> topDiscard();
    // Gets the players score
    int getPlayerScore(int index);
    // Returns whether or not the round is over
    bool roundOver();
    // Returns whether or not the game is over
    bool gameOver();
    // Returns whether or the current move is the first
    bool firstMove();
};

#endif
