#include <vector>
#include <memory>
#include <algorithm>
#include "player.h"
#include "card.h"

Player::Player(Board *model) : score{0}, model{model} {}

void Player::addCard(Card c) {
    // Makes a shared pointer to card c and adds it to the hand
    auto tmp = make_shared<Card>(c);
    hand.push_back(tmp);
}

void Player::playedCard(Card c) {
    // Iterates through the hand
    for (unsigned int i = 0; i < hand.size(); i++) {
        // Checks if the card at position i of the hand is the card c
        if (*(hand.at(i)) == c) {
            // Removes this card from the hand
            // std::remove moves the pointer to the card to the end and
            // erase removes everything passed the iterator returned from remove
            hand.erase(std::remove(hand.begin(),hand.end(),hand.at(i)));
        }
    }
}

void Player::discardCard(Card c) {
    for (unsigned int i = 0; i < hand.size(); i++) {
        // Checks if the card at position i of the hand is the card c
        if (*(hand.at(i)) == c) {
            // pushes the card to the end of the discard pile
            discardpile.push_back((hand.at(i)));
            // Marks the card as played (removed from hand)
            playedCard(c);
        }
    }
}

bool Player::willStart() {
    // This is the start card: 7S
    Card startcard{Seven, Spade};
    // Iterates through the hand and checks if the 7S is in the hand
    for (unsigned int i = 0; i < hand.size(); i++) {
        if (*(hand.at(i)) == startcard) {
            return true;
        }
    }
    return false;
}

int Player::getScore() {
    return score;
}

void Player::updateScore() {
    score = totalScore();
}

int Player::roundScore() {
    int sum = 0;
    // Goes through the discard pile and adds to the sum the value of
    // the card at index i
    for (unsigned int i = 0; i < discardpile.size(); i++) {
        sum += (*(discardpile.at(i))).getValue();
    }
    return sum;
}

int Player::totalScore() {
    int sum;
    // Adds the current score to the score from the current round
    sum = score + roundScore();
    return sum;
}

vector<shared_ptr<Card>> Player::getHand() const {
    return hand;
}

vector<shared_ptr<Card>> Player::getDiscard() const {
    return discardpile;
}

vector<shared_ptr<Card>> Player::getValidPlays() const {
    // Creates a temporary vector of pointers to cards
    vector<shared_ptr<Card>> validmoves;
    // If it is the first move, only valid move is 7S
    if (model->firstMove()) {
        Card startcard{Seven, Spade};
        validmoves.push_back(make_shared<Card>(startcard));
    } else {
        // Goes through the cards that have been played
        for (auto curcard : model->getPlayed()) {
            // Goes through the hand of the player
            for (unsigned int i = 0; i < hand.size(); i++) {
                // Any card that is a seven is a valid play
                if (hand.at(i)->getRank() == Seven)  {
                    // Prevent duplicates
                    if (!(find(validmoves.begin(), validmoves.end(), hand.at(i)) != validmoves.end())) {
                        validmoves.push_back(hand.at(i));
                    }
                } else if (hand.at(i)->getSuit() == curcard->getSuit()) {
                    // Any card with the same suit and different rank by 1 is a valid play
                    if (hand.at(i)->getRank() == curcard->getRank() + 1) {
                        // Checks if the rank is one higher than the card
                        // Prevent duplicates
                        if (!(find(validmoves.begin(), validmoves.end(), hand.at(i)) != validmoves.end())) {
                        validmoves.push_back(hand.at(i));
                        }
                    } else if (hand.at(i)->getRank() == curcard->getRank() - 1) {
                        // Checks if the rank is one lower than the card
                        // Prevent duplicates
                        if (!(find(validmoves.begin(), validmoves.end(), hand.at(i)) != validmoves.end())) {
                        validmoves.push_back(hand.at(i));
                        }
                    }
                }
            }
        }
    }
    // Returns this vector of valid moves
    return validmoves;
}

void Player::setHand(std::vector<std::shared_ptr<Card>> h) {
    hand = h;
}

void Player::setDiscard(std::vector<std::shared_ptr<Card>> d) {
    discardpile = d;
}

void Player::setScore(int s) {
    score = s;
}

void Player::reset() {
    hand.clear();
    discardpile.clear();
}
