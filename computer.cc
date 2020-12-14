#include "computer.h"
#include "move.h"
#include "player.h"
using namespace std;

Computer::Computer(Board *model) : Player{model} {}

Move Computer::play(Card c, bool mtype) {
    // Creates a temporary move that will be returned
    Move tmp{};
    // Gets the valid cards that this computer can play
    vector<shared_ptr<Card>> validmoves = getValidPlays();
    // If there are valid cards that can be played, then play a card
    if (validmoves.size() > 0) {
        tmp.setType(MoveType::Play);
    } else {
        tmp.setType(MoveType::Discard);
    }
    // If it is currently the first move, then the only valid play is 7S
    if (model->firstMove()) {
        Card sevenspade = Card(Seven,Spade);
        tmp.setCard(sevenspade);
    } else if (tmp.getType() == MoveType::Discard) {
        // The computer discards the first card in our hand
        tmp.setCard(*(hand.at(0)));
    } else if (tmp.getType() == MoveType::Play) {
        // The computer plays the first card in the valid list of cards to play
        tmp.setCard(*(validmoves.at(0)));
    }
    // Return this move
    return tmp;
}

PlayerType Computer::getType() const {
    return PlayerType::Computer;
}
