#include "board.h"
#include "player.h"
#include "deck.h"
#include "human.h"
#include "computer.h"
#include <vector>
#include <memory>
using namespace std;

ArgExn::ArgExn( std::string message ): message{message} {}

Board::Board() : roundnum{0}, curplayer{0} {
    auto tmp = make_shared<Deck>();
    deck = tmp;
}

Board::Board(int seed) : roundnum{0}, curplayer{0} {
    auto tmp = make_shared<Deck>(seed);
    deck = tmp;
}

void Board::setSeed(int s) {
    deck->setSeed(s);
}

void Board::addPlayer(PlayerType type) {
    if (type == PlayerType::Computer) {
        auto tmp = make_shared<Computer>(this);
        players.push_back(tmp);
    } else {
        auto tmp = make_shared<Human>(this);
        players.push_back(tmp);
    }
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
    auto oldhuman = players.at(curplayer);
    auto tmp = make_shared<Computer>(this);
    tmp->setHand(oldhuman->getHand());
    tmp->setDiscard(oldhuman->getDiscard());
    tmp->setScore(oldhuman->getScore());
    players.erase(players.begin() + curplayer);
    players.insert(players.begin() + curplayer, tmp);
    notify(State::RAGEQUIT);
}

void Board::makeMove(Card c, bool mtype) {
    Move tmp = players.at(curplayer)->play(c, mtype);
    MoveType type = tmp.getType();
    Card movecard = tmp.getCard();
    if (type == MoveType::Play) {
        shared_ptr<Card> tmp = make_shared<Card>(movecard.getRank(),movecard.getSuit());
        cards.push_back(tmp);
        players.at(curplayer)->playedCard(movecard);
        firstplay = false;
        notify(State::PLAY);
    } else if (type == MoveType::Discard) {
        players.at(curplayer)->discardCard(movecard);
        notify(State::DISCARD);
    } else if (type == MoveType::None && mtype) {
        throw ArgExn("This is not a legal play");
    } else if (type == MoveType::None && !mtype) {
        throw ArgExn("You have a legal play. You may not discard");
    }
    curplayer++;
    if (curplayer == 4) {
        curplayer = 0;
    }
    if (players.at(curplayer)->getType() == PlayerType::Human || roundOver()) {
        notify(State::PRINTCARD);
    }
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
}

int Board::getCurrentPlayer() {
    return curplayer;
}

vector<shared_ptr<Card>> Board::getDeck() {
    return deck->getCards();
}

vector<shared_ptr<Card>> Board::getPlayed() {
    return cards;
}

vector<shared_ptr<Card>> Board::getHand() {
    return players.at(curplayer)->getHand();
}

vector<shared_ptr<Card>> Board::getDiscard() {
    return players.at(curplayer)->getDiscard();
}

vector<shared_ptr<Card>> Board::getValidPlays() {
    return players.at(curplayer)->getValidPlays();
}

vector<shared_ptr<Player>> Board::getPlayers() {
    return players;
}

PlayerType Board::getPlayerType() {
    return players.at(curplayer)->getType();
}

void Board::start() {
    cards.clear();
    roundnum = 0;
    nextRound();
}

void Board::nextRound() {
    firstplay = true;
    cards.clear();
    roundnum++;
    for (shared_ptr<Player> player : players) {
        player->reset();
    }
    deck->shuffle();
    dealCard();
    setStart();
    notify(State::NEWROUND);
    if (players.at(curplayer)->getType() == PlayerType::Human) {
        notify(State::PRINTCARD);
    }
}

shared_ptr<Card> Board::topCard() {
    return cards.at(cards.size() - 1);
}

shared_ptr<Card> Board::topDiscard() {
    vector<shared_ptr<Card>> tmp = getDiscard();
    return tmp.at(tmp.size() - 1);
}

int Board::getPlayerScore(int index) {
    return (players.at(index))->totalScore();
}

bool Board::roundOver() {
   for (int i = 0; i < players.size(); i++) {
       if (!(players.at(i)->getHand().empty())) {
           return false;
       }
   }
   notify(State::ENDROUND);
   for (shared_ptr<Player> player : players) {
        player->updateScore();
    }
   return true;
}

bool Board::gameOver() {
     for (int i = 0; i < players.size(); i++) {
        if (players.at(i)->getScore() >= 80) {
            notify(State::ENDGAME);
            return true;
        }
    }
    return false;
}

bool Board::firstMove() {
    return firstplay;
}
