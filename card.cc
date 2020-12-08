#include "card.h"
using namespace std;

Card::Card(Rank rank, Suit suit) : suit{cardsuit}, rank{cardrank} {}

Suit Card::getSuit() const {
    return cardsuit;
}

Rank Card::getRank() const {
    return cardrank;
}
