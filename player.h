#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
#include "move.h"
#include "board.h"
#include <vector>
#include <memory>

class Board;
enum class PlayerType { Human, Computer };

class Player {
protected:
    // The score of the player
    int score;
    // What cards the player has discarded
    std::vector<std::shared_ptr<Card>> discardpile;
    // What cards are in the players hand
    std::vector<std::shared_ptr<Card>> hand;
    // Stores the current board that the player is playing on
    Board *model;
public:
    // Constructs a player with the given board
    Player(Board *model);
    // Adds card to hand of the player
    void addCard(Card c);
    // Marks the card as played: removes the card from the hand of the player
    void playedCard(Card c);
    // Discards the given card from the hand
    void discardCard(Card c);
    // Whether or not the player will start the game (has seven of spades)
    bool willStart();
    // Returns the score of the player
    int getScore();
    // Updates the score: This is used at the end of the round
    void updateScore();
    // Computes the new score of the player (after a round has completed)
    int roundScore();
    // Return the total score
    int totalScore();
    // Returns the hand of the player
    std::vector<std::shared_ptr<Card>> getHand() const;
    // Returns the discarded cards of the player
    std::vector<std::shared_ptr<Card>> getDiscard() const;
    // Returns the list of valid plays for this player
    std::vector<std::shared_ptr<Card>> getValidPlays() const;
    // Sets the hand of the player
    void setHand(std::vector<std::shared_ptr<Card>> h);
    // Sets the discarded cards of the player
    void setDiscard(std::vector<std::shared_ptr<Card>> d);
    // Sets the score of a player
    void setScore(int s);
    // Makes a play: This will delegate the play to either the computer or
    // Player depending on what type of player this player is
    // mtype == true represents a play and mtype == false represents discard
    virtual Move play(Card c, bool mtype) = 0;
    // Gets the type of player
    virtual PlayerType getType() const = 0;
    // Resets the hand and discard of the current player
    void reset();
};

#endif
