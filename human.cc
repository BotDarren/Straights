#include "human.h"
#include "move.h"
#include "player.h"
using namespace std;

Human::Human(Board *model) : Player{model} {}

Move Human::play(Card c, bool mtype) {
    // Creates a temporary move to be returned
    Move tmp{};
    // Gets the valid cards that can be played
    vector<shared_ptr<Card>> validmoves = getValidPlays();
    // Whether the card we are trying to use is in the valid plays
    bool inmoves = false;
    // Whether the card we are trying to use is in the hand of the player
    bool inhand = false;
    // Sets whether the card we are trying to use is in the valid plays
    for (shared_ptr<Card> moves : validmoves) {
        if (c == *moves) {
            inmoves = true;
        }
    }
    // Sets whether the card we are trying to use is in the hand of the player
    for (shared_ptr<Card> handcard : getHand()) {
        if (c == *handcard) {
            inhand = true;
        }
    }
    // If there are valid moves and the card we are using is in the moves then we
    // can play. mtype == true represents that the human is making a move
    if (validmoves.size() > 0 && inmoves && mtype) {
        tmp.setType(MoveType::Play);
    } else if ((validmoves.size() == 0) && inhand && !mtype) {
        // If there are no valid moves, and the card we are trying to play is in the hand
        // of the player, then we can discard. mtype == false represents the human is discarding
        tmp.setType(MoveType::Discard);
    } else {
        // If we are neither discarding nor playing then this is an invalid move: None is used to set
        // off the exception
        tmp.setType(MoveType::None);
    }
    // Sets the card to the given card
    tmp.setCard(c);
    return tmp;
}

PlayerType Human::getType() const {
    return PlayerType::Human;
}
