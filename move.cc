#include "move.h"
using namespace std;

Move::Move() : movetype{MoveType::None}, card(Jack, Club) {}

void Move::setType(MoveType type) {
    movetype = type;
}

void Move::setCard(Card c) {
    card = c;
}

MoveType Move::getType() {
    return movetype;
}

Card Move::getCard() {
    return card;
}
