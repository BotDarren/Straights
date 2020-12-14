#include "move.h"
using namespace std;

Move::Move() : movetype{MoveType::None}, card(Jack, Club) {}

void Move::setType(MoveType type) {
    movetype = type;
}

void Move::setCard(Card c) {
    card = c;
}

MoveType Move::getType() const {
    return movetype;
}

Card Move::getCard() const {
    return card;
}
