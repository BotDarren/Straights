#ifndef DECK_H
#define DECK_H
#include <vector>
#include <memory>
#include <chrono>
#include "card.h"

class Deck {
    // Stores the current cards in the deck (in order)
    std::vector<std::shared_ptr<Card>> cards;
    // Stores the current seed of the deck: default seed of the current time
    // This code is copied from the shuffle.cc file that was provided
    int seed = std::chrono::system_clock::now().time_since_epoch().count();;
public:
    // Constructor for the deck without a seed
    Deck();
    // Constructor for deck with a seed
    Deck(int seed);
    // Returns the seed that the deck is using
    unsigned int getSeed();
    // Shuffles the deck with the given seed
    void shuffle();
    // Returns the cards in the deck
    std::vector<std::shared_ptr<Card>> getCards() const;
};

// This is used to print a deck
std::ostream &operator<<(std::ostream &out, const Deck &deck);

#endif
