#include <vector>
#include <memory>
#include "player.h"
#include "card.h"

Player::Player(PlayerType type, Board *model) : type{type}, model{model} {}

void Player::addCard(Card c) {
    hand.emplace_back(c);
}

void Player::switchType() {
    if (type == Human) {
        type == Computer;
    } else if (type == Computer) {
        type == Human;
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
