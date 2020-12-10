#include "card.h"
#include <string>
#include <ostream>
#include <istream>
using namespace std;

Card::Card(Rank rank, Suit suit) : cardsuit{suit}, cardrank{rank} {}

Suit Card::getSuit() const {
    return cardsuit;
}

Rank Card::getRank() const {
    return cardrank;
}

// Apparently an enum can return an integer corresponding to which element it is in the enum
// ** Make sure to test **
int Card::getValue() const {
    return getRank() + 1;    
}

// Couldn't find an elegant way of doing this
std::ostream &operator<<(std::ostream &out, const Card &c) {
    Rank crank = c.getRank();
    Suit csuit = c.getSuit(); 
    if (crank == Ace) {
        out << "A";
    } else if (crank == Two) {
        out << "2";
    } else if (crank == Three) {
        out << "3";
    } else if (crank == Four) {
        out << "4";
    } else if (crank == Five) {
        out << "5";
    } else if (crank == Six) {
        out << "6";
    } else if (crank == Seven) {
        out << "7";
    } else if (crank == Eight) {
        out << "8";
    } else if (crank == Nine) {
        out << "9";
    } else if (crank == Ten) {
        out << "10";
    } else if (crank == Jack) {
        out << "J";
    } else if (crank == Queen) {
        out << "Q";
    } else if (crank == King) {
        out << "K";
    }

    if (csuit == Club) {
        out << "C";
    } else if (csuit == Diamond) {
        out << "D";
    } else if (csuit == Heart) {
        out << "H";
    } else if (csuit == Spade) {
        out << "S";
    }
    return out;
}

std::istream &operator>>(std::istream &in, Card &card) {
    // Stores the possible suits
    string suits = "CDHS";
    // Stores the possible ranks
    string ranks = "A234567891JQK";
    string tmp;
    in >> tmp;
    // Finds the rank and sets the card rank to it
    card.cardrank = (Rank)ranks.find(tmp.at(0));
    // Finds the suit and sets the card suit to it
    if (card.cardrank == Ten) {
        card.cardsuit = (Suit)suits.find(tmp.at(2));
    } else {
        card.cardsuit = (Suit)suits.find(tmp.at(1));
    }
}

bool operator==(const Card &c1, const Card &c2) {
    return ((c1.getRank() == c2.getRank()) && (c1.getSuit() == c2.getSuit()));
}
