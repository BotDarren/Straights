#include "board.h"
#include "player.h"
#include "deck.h"
#include "human.h"
#include "computer.h"
#include <vector>
#include <memory>
using namespace std;

Board::Board() : topscore{0}, roundnum{0}, curplayer{0} {
    auto tmp = make_shared<Deck>();
    deck = tmp;
    seed = deck->getSeed();
}

Board::Board(int seed) : topscore{0}, roundnum{0}, seed{seed}, curplayer{0} {
    auto tmp = make_shared<Deck>(seed);
    deck = tmp;
}

void Board::setSeed(int s) {
    seed = s;
}

void Board::addPlayer(PlayerType type) {
    if (type == PlayerType::Computer) {
        auto tmp = make_shared<Computer>(this);
        players.push_back(tmp);
    } else {
        auto tmp = make_shared<Human>(this);
        players.push_back(tmp);
    }
    notify(curstate);
}

void Board::setStart() {
    for (int i = 0; i < players.size(); i++) {
        if (players.at(i)->willStart()) {
            curplayer = i;
        }
    }
    firstplay = true;
}

void Board::rage() {
    players.at(curplayer)->switchType();
    notify(curstate);
}

void Board::makeMove(Card c) {
    Move tmp = players.at(curplayer)->play(c);
    MoveType type = tmp.getType();
    Card movecard = tmp.getCard();
    if (type == MoveType::Play) {
        cards.emplace_back(c);
        players.at(curplayer)->playedCard(c);
    } else if (type == MoveType::Discard) {
        players.at(curplayer)->discardCard(c);
    }
    notify(curstate);
}

void Board::dealCard() {
    vector<shared_ptr<Card>> curdeck = deck->getCards();
    for (int i = 0; i < 13; i++) {
        players.at(0)->addCard(*(curdeck.at(i)));
    }
    for (int i = 13; i < 26; i++) {
        players.at(1)->addCard(*(curdeck.at(i)));
    }
    for (int i = 26; i < 39; i++) {
        players.at(2)->addCard(*(curdeck.at(i)));
    }
    for (int i = 39; i < 52; i++) {
        players.at(3)->addCard(*(curdeck.at(i)));
    }
    notify(curstate);
}

void Board::start() {}

void Board::nextRound() {

}

shared_ptr<Card> Board::topCard() {
    return cards.at(cards.size() - 1);
}

int Board::getPlayerScore(int index) {
    return (players.at(index))->totalScore();
}

bool Board::roundOver() {
   for (int i = 0; i < 4; i++) {
       if (!players.at(i)->getHand().empty()) {
           return false;
       }
   }
   return true;
}

bool Board::gameOver() {
     for (int i = 0; i < 4; i++) {
        if (players.at(i)->totalScore() >= 80) {
            return true;
        }
    }
    return false;
}

bool Board::firstMove() {
    return firstplay;
}

vector<int> Board::getWinners() {
    vector<int> winners;
    for (int i = 0; i < 4; i++) {
        if (players.at(i)->totalScore() >= 80) {
            winners.push_back(i);
        }
    }
    return winners;
}

