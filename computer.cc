#include "computer.h"
#include "move.h"
#include "player.h"
#include "board.h"
using namespace std;

Computer::Computer(Board *model) : Player{model} {}

Move Computer::play(Card c, bool mtype) {
    Move tmp{};
    vector<shared_ptr<Card>> validmoves = getValidPlays();
    if (validmoves.size() > 0) {
        tmp.setType(MoveType::Play);
    } else {
        tmp.setType(MoveType::Discard);
    }
    if (model->firstMove()) {
        Card sevenspade = Card(Seven,Spade);
        tmp.setCard(sevenspade);
    } else if (tmp.getType() == MoveType::Discard) {
        tmp.setCard(*(hand.at(0)));
    } else if (tmp.getType() == MoveType::Play) {
        tmp.setCard(*(validmoves.at(0)));
    }
    return tmp;
}

PlayerType Computer::getType() {
    return PlayerType::Computer;
}

