#include <vector>
#include <memory>
#include <algorithm>
#include "player.h"
#include "card.h"

Player::Player(Board *model) : model{model}, score{0} {}

void Player::addCard(Card c) {
    auto tmp = make_shared<Card>(c);
    hand.push_back(tmp);
}

void Player::playedCard(Card c) {
    for (int i = 0; i < hand.size(); i++) {
        if (*(hand.at(i)) == c) {
            hand.erase(std::remove(hand.begin(),hand.end(),hand.at(i)));
        }
    }
}

void Player::discardCard(Card c) {
    for (int i = 0; i < hand.size(); i++) {
        if (*(hand.at(i)) == c) {
            discardpile.push_back((hand.at(i)));
            playedCard(c);
        }
    }
}

bool Player::willStart() {
    Card startcard{Seven, Spade};
    for (int i = 0; i < hand.size(); i++) {
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
    for (int i = 0; i < discardpile.size(); i++) {
        sum += (*(discardpile.at(i))).getValue();
    }
    return sum;
}

int Player::totalScore() {
    int sum;
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
    vector<shared_ptr<Card>> validmoves;
    if (model->firstMove()) {
        Card startcard{Seven, Spade};
        validmoves.push_back(make_shared<Card>(startcard));
    } else {
        for (auto curcard : model->getPlayed()) {
            for (int i = 0; i < hand.size(); i++) {
                if (hand.at(i)->getRank() == Seven)  {
                    // Prevent duplicates
                    if (!(find(validmoves.begin(), validmoves.end(), hand.at(i)) != validmoves.end())) {
                        validmoves.push_back(hand.at(i));
                    }
                } else if (hand.at(i)->getSuit() == curcard->getSuit()) {
                    if (hand.at(i)->getRank() == curcard->getRank() + 1) {
                        // Prevent duplicates
                        if (!(find(validmoves.begin(), validmoves.end(), hand.at(i)) != validmoves.end())) {
                        validmoves.push_back(hand.at(i));
                        }
                    } else if (hand.at(i)->getRank() == curcard->getRank() - 1) {
                        // Prevent duplicates
                        if (!(find(validmoves.begin(), validmoves.end(), hand.at(i)) != validmoves.end())) {
                        validmoves.push_back(hand.at(i));
                        }
                    }
                }
            }
        }
    }
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
