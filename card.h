#ifndef CARD_H
#define CARD_H

// The possible suits of cards
enum class Suit { Club, Diamond, Heart, Spade };
// The possible ranks of cards
enum class Rank { Ace, One, Two, Three, Four, Five, Six, 
                Seven, Eight, Nine, Ten, Jack, Queen, King };

class Card {
    Suit cardsuit;
    Rank cardrank;
   public:        
    // Constructor for a card, given its rank and its suit
    Card(Rank cardrank, Suit cardsuit);
    // Returns the suit of the card
    Suit getSuit() const;
    // Returns the rank of the card
    Rank getRank() const;
};

#endif
