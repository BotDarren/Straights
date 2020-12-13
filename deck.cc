#include "deck.h"
#include "card.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

Deck::Deck() {
    for (int i = 0; i < numSuits; i++) {
        for (int n = 0; n < numRanks; n++) {
            shared_ptr<Card> tmp = make_shared<Card>(static_cast<Rank>(n),static_cast<Suit>(i));
            cards.push_back(tmp);
        }
    }
}

Deck::Deck(int seed) : seed{seed} {
    for (int i = 0; i < numSuits; i++) {
        for (int n = 0; n < numRanks; n++) {
            shared_ptr<Card> tmp = make_shared<Card>(static_cast<Rank>(n),static_cast<Suit>(i));
            cards.push_back(tmp);
        }
    }
}

unsigned int Deck::getSeed() {
    return seed;
}

void Deck::setSeed(unsigned int s) {
    seed = s;
}

// This function is based on the shuffle.cc that was provided for this project
void Deck::shuffle() {
    std::default_random_engine rng{seed};
	std::shuffle( cards.begin(), cards.end(), rng );
}

vector<shared_ptr<Card>> Deck::getCards() const {
    return cards;
}

std::ostream &operator<<(std::ostream &out, const Deck &deck) {
    int curcount = 0;
    int numcards = numSuits * numRanks;
    vector<shared_ptr<Card>> deckcards = deck.getCards();
    for (int i = 0; i < numcards; i++) {
        if (curcount == 13) {
            out << endl << *(deckcards.at(i));
        } else {
            out << *(deckcards.at(i));
        }
    }
    return out;
}
