#include <vector>
#include <memory>
#include <algorithm>
#include "player.h"
#include "card.h"

Player::Player(PlayerType type, Board *model) : type{type}, model{model} {}

void Player::addCard(Card c) {
    auto tmp = make_shared<Card>(c);
    hand.push_back(tmp);
}

void Player::playedCard(Card c) {
    // Used to store the index where the card c is in the hand of the player
    int index;
    for (int i = 0; i < hand.size(); i++) {
        if (*(hand.at(i)) == c) {
            index = i;
        }
    }
    // Remove the shared pointer at the specified index
    hand.erase(std::remove(hand.begin(),hand.end(),hand.at(index)));

}

void Player::discardCard(Card c) {
    for (int i = 0; i < hand.size(); i++) {
        if (*(hand.at(i)) == c) {
            discardpile.push_back((hand.at(i)));
            playedCard(c);
        }
    }
}

void Player::switchType() {
    if (type == PlayerType::Human) {
        type == PlayerType::Computer;
    } else if (type == PlayerType::Computer) {
        type == PlayerType::Human;
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

int Player::roundScore() {
    int sum;
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
        shared_ptr<Card> curcard = model->topCard();
        for (int i = 0; i < hand.size(); i++) {
            if (hand.at(i)->getRank() == Seven)  {
                validmoves.push_back(hand.at(i));
            } else if (hand.at(i)->getSuit() == curcard->getSuit()) {
                if (hand.at(i)->getRank() == curcard->getRank() + 1) {
                    validmoves.push_back(hand.at(i));
                } else if (hand.at(i)->getRank() == curcard->getRank() - 1) {
                    validmoves.push_back(hand.at(i));
                }
            }
        }
    }
    return validmoves;
}
