#ifndef DECK_H
#define DECK_H
#include <memory>
#include "card.h"

class Deck {
    // Stores the current cards in the deck (in order)
    std::vector<std::shared_ptr<Card>> cards;
    // Stores the current seed of the deck
    int seed;
public:
    // Constructor for the deck given the seed
    Deck(int seed);
    // Shuffles the deck with the given seed
    void shuffle(int seed);
    // Returns the cards in the deck
    std::vector<std::shared_ptr<Card>> getCards();
};

#endif
