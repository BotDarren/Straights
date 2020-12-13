#include "text_view.h"
#include "human.h"
#include "move.h"
#include "player.h"
#include "board.h"
using namespace std;

Human::Human(Board *model) : Player{model} {}

Move Human::play(Card c, bool mtype) {
    Move tmp{};
    vector<shared_ptr<Card>> validmoves = getValidPlays();
    bool inmoves = false;
    bool inhand = false;
    for (shared_ptr<Card> moves : validmoves) {
        if (c == *moves) {
            inmoves = true;
        }
    }
    for (shared_ptr<Card> handcard : getHand()) {
        if (c == *handcard) {
            inhand = true;
        }
    }
    if (validmoves.size() > 0 && inmoves && mtype) {
        tmp.setType(MoveType::Play);
    } else if ((validmoves.size() == 0) && inhand && !mtype) {
        tmp.setType(MoveType::Discard);
    } else {
        tmp.setType(MoveType::None);
    }
    tmp.setCard(c);
    return tmp;
}

PlayerType Human::getType() {
    return PlayerType::Human;
}
