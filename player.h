#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"
#include <vector>
#include <memory>

enum class PlayerType { Human, Computer };

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
public:
    // Constructs a player with the given type
    Player(PlayerType type);
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
    // Recalculates the valid plays of the player
    void recalculateValid();
    // Returns the list of valid plays for this player
    const std::vector<shared_ptr<Card>> getValidPlays();
}

#endif
