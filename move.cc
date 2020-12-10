#include "move.h"
using namespace std;

Move::Move() : movetype{MoveType::None} {
    Card tmp = Card{Jack, Club};
    card = tmp;
}

void Move::setType(MoveType type) {
    movetype = type;
}

void Move::setCard(Card c) {
    card = c;
}
