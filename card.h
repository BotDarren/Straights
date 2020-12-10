#ifndef CARD_H
#define CARD_H
#include <ostream>
#include <istream>
using namespace std;

const int numRanks = 13;
const int numSuits = 4;
// The possible suits of cards
enum Suit { Club, Diamond, Heart, Spade };
// The possible ranks of cards
enum Rank { Ace, Two, Three, Four, Five, Six, 
                Seven, Eight, Nine, Ten, Jack, Queen, King };

class Card {
    friend istream &operator>>(std::istream &in, Card &card);
    Suit cardsuit;
    Rank cardrank;
   public:        
    // Constructor for a card, given its rank and its suit
    Card(Rank cardrank, Suit cardsuit);
    // Returns the suit of the card
    Suit getSuit() const;
    // Returns the rank of the card
    Rank getRank() const;
    // Returns the value of the card: the integer value
    int getValue() const;
};

// This is used to print a card to output
ostream &operator<<(ostream &out, const Card &c);
// This is used to input the card information into the respective card
istream &operator>>(istream &in, Card &c);
// This is used to compare the two cards and see if they are equal: same rank & suit
bool operator==(const Card &c1, const Card &c2);

#endif
