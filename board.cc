#include "board.h"
#include "player.h"
#include "deck.h"
#include "human.h"
#include "computer.h"
using namespace std;

Board::Board(int seed) : topscore{0}, roundnum{0}, seed{seed}, curplayer{0} {
    Deck tmp = Deck(seed);
    deck = tmp;
}

void Board::addPlayer(PlayerType type) {
    if (type == PlayerType::Computer) {
        auto tmp = Computer::Computer{this};
        players.push_back(tmp);
    } else {
        auto tmp = Human::Human{this};
        players.push_back(tmp);
    }
}

void Board::setStart() {
    for (int i = 0; i < players.size(); i++) {
        if (players.at(i).willStart()) {
            curplayer = i;
        }
    }
}

void Board::makeMove() {
    Move tmp = players.at(curplayer).play();
    // Not finished
}

void Board::dealCard() {
    vector<shared_ptr<Card>> curdeck = deck.getCards();
    for (int i = 0; i < 13; i++) {
        players.at(0).addCard(*(curdeck.at(i)));
    }
    for (int i = 13; i < 26; i++) {
        players.at(1).addCard(*(curdeck.at(i)));
    }
    for (int i = 26; i < 39; i++) {
        players.at(2).addCard(*(curdeck.at(i)));
    }
    for (int i = 39; i < 52; i++) {
        players.at(3).addCard(*(curdeck.at(i)));
    }
}

void Board::start() {}

Card Board::topCard() {
    return cards.at(cards.size() - 1);
}

int Board::getPlayerScore(int index) {
    return (players.at(index)).totalScore();
}

bool Board::roundOver()

bool Board::gameOver()

bool Board::firstMove()

vector<int> Board::getWinners()

