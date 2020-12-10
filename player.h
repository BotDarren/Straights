#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
#include "move.h"
#include "board.h"
#include <vector>
#include <memory>

enum PlayerType { Human, Computer };

class Player {
protected:
    // The score of the player
    int score = 0;
    // What cards the player has discarded
    std::vector<std::shared_ptr<Card>> discardpile;
    // What cards are in the players hand
    std::vector<std::shared_ptr<Card>> hand;
    // What cards can the player play
    std::vector<std::shared_ptr<Card>> validplays;
    // What type of player: human/computer
    PlayerType type;
    // Stores the current board that the player is playing on
    Board *model;
public:
    // Constructs a player with the given type
    Player(PlayerType type, Board *model);
    // Adds card to hand
    void addCard(Card c);
    // Switches the type of player: from human -> computer or vice versa
    void switchType();
    // Whether or not the player will start the game (has seven of spades)
    bool willStart();
    // Computes the new score of the player (after a round has completed)
    int roundScore();
    // Return the total score
    int totalScore();
    // Returns the list of valid plays for this player
    std::vector<std::shared_ptr<Card>> getValidPlays() const;
    // Makes a play: Depending on the player, this will be delegated to a computer/human player
    // This can either be playing a card or discarding a card
    virtual Move play() = 0;
};

#endif
