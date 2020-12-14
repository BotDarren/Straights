#include "board.h"
#include "player.h"
#include "deck.h"
#include "human.h"
#include "computer.h"
#include <vector>
#include <memory>
using namespace std;

ArgExn::ArgExn( std::string message ): message{message} {}

Board::Board() : curplayer{0} {
    // Makes a deck and assigns the deck to this board
    auto tmp = make_shared<Deck>();
    deck = tmp;
}

Board::Board(unsigned int seed) : curplayer{0} {
    // Makes a deck and assigns the deck to this board
    auto tmp = make_shared<Deck>(seed);
    deck = tmp;
}

void Board::setSeed(unsigned int s) {
    deck->setSeed(s);
}

void Board::addPlayer(PlayerType type) {
    if (type == PlayerType::Computer) {
        // Makes a computer player and pushes it to the player list
        auto tmp = make_shared<Computer>(this);
        players.push_back(tmp);
    } else {
        // Makes a human player and pushes it to the player list
        auto tmp = make_shared<Human>(this);
        players.push_back(tmp);
    }
}

void Board::setStart() {
    for (unsigned int i = 0; i < players.size(); i++) {
        // Goes through the players and checks if they have the 7S card
        // If they do then they are set as the beginning player
        if (players.at(i)->willStart()) {
            curplayer = i;
        }
    }
    firstplay = true;
}

void Board::rage() {
    // Creates a new computer player with the same hand, discard pile, score
    auto oldhuman = players.at(curplayer);
    auto tmp = make_shared<Computer>(this);
    tmp->setHand(oldhuman->getHand());
    tmp->setDiscard(oldhuman->getDiscard());
    tmp->setScore(oldhuman->getScore());
    // Remove the human player from the player list and insert the computer player
    players.erase(players.begin() + curplayer);
    players.insert(players.begin() + curplayer, tmp);
    notify(State::RAGEQUIT);
}

void Board::makeMove(Card c, bool mtype) {
    // Gets the move that will be done through the play function of the Player class
    Move tmp = players.at(curplayer)->play(c, mtype);
    MoveType type = tmp.getType();
    Card movecard = tmp.getCard();
    if (type == MoveType::Play) {
        // Makes a card with the rank and suit of the intended card from the returned Move
        shared_ptr<Card> tmp = make_shared<Card>(movecard.getRank(),movecard.getSuit());
        // Pushes it to the list of played cards on the board
        cards.push_back(tmp);
        // Indicates to the player that the card is played
        players.at(curplayer)->playedCard(movecard);
        firstplay = false;
        notify(State::PLAY);
    } else if (type == MoveType::Discard) {
        // Indicates to the player that the card is discarded
        players.at(curplayer)->discardCard(movecard);
        notify(State::DISCARD);
    } else if (type == MoveType::None && mtype) {
        // If the given play is not possible
        throw ArgExn("This is not a legal play");
    } else if (type == MoveType::None && !mtype) {
        // If the given discard is not possible
        throw ArgExn("You have a legal play. You may not discard");
    }
    // Increment the player
    curplayer++;
    if (curplayer == 4) {
        // If player = 4, then we change it back to 0 to wrap around the list of players
        curplayer = 0;
    }
    if (players.at(curplayer)->getType() == PlayerType::Human && !roundover && !gameover) {
        // Only notify to print table if the round is not over, game is not over
        // and the current player is a human
        notify(State::PRINTTABLE);
    }
}

void Board::dealCard() {
    // Gets the cards in the deck
    vector<shared_ptr<Card>> curdeck = deck->getCards();
    // Assigns 13 cards to each of the players
    for (unsigned int i = 0; i < 13; i++) {
        players.at(0)->addCard(*(curdeck.at(i)));
    }
    for (unsigned int i = 13; i < 26; i++) {
        players.at(1)->addCard(*(curdeck.at(i)));
    }
    for (unsigned int i = 26; i < 39; i++) {
        players.at(2)->addCard(*(curdeck.at(i)));
    }
    for (unsigned int i = 39; i < 52; i++) {
        players.at(3)->addCard(*(curdeck.at(i)));
    }
}

int Board::getCurrentPlayer() const {
    return curplayer;
}

vector<shared_ptr<Card>> Board::getDeck() const {
    return deck->getCards();
}

vector<shared_ptr<Card>> Board::getPlayed() const {
    return cards;
}

vector<shared_ptr<Card>> Board::getHand() const {
    return players.at(curplayer)->getHand();
}

vector<shared_ptr<Card>> Board::getDiscard() const {
    return players.at(curplayer)->getDiscard();
}

vector<shared_ptr<Card>> Board::getValidPlays() const {
    return players.at(curplayer)->getValidPlays();
}

vector<shared_ptr<Player>> Board::getPlayers() const {
    return players;
}

PlayerType Board::getPlayerType() const {
    return players.at(curplayer)->getType();
}

void Board::start() {
    cards.clear();
    gameover = false;
    roundover = false;
    nextRound();
}

void Board::nextRound() {
    firstplay = true;
    cards.clear();
    roundover = false;
    // Resets each of the players hand and discard pile
    for (shared_ptr<Player> player : players) {
        player->reset();
    }
    deck->shuffle();
    dealCard();
    // Sets the player that will start the round: player with 7S
    setStart();
    // Checks if the game is over
    if (!gameOver()) {
        notify(State::NEWROUND);
        // If the current player is human, then we print the table
        if (players.at(curplayer)->getType() == PlayerType::Human) {
            notify(State::PRINTTABLE);
        }
    }
}

shared_ptr<Card> Board::topCard() {
    return cards.at(cards.size() - 1);
}

shared_ptr<Card> Board::topDiscard() {
    vector<shared_ptr<Card>> tmp = getDiscard();
    return tmp.at(tmp.size() - 1);
}

int Board::getPlayerScore(int index) const {
    return (players.at(index))->totalScore();
}

bool Board::roundOver() {
    // Iterates through all the players hand and if one hand is not empty
    // then the round is not over yet
    for (unsigned int i = 0; i < players.size(); i++) {
       if (!(players.at(i)->getHand().empty())) {
            return false;
       }
    }
    // Makes sure that if the round is already over, we don't print the message again
    if (!roundover) {
        notify(State::ENDROUND);
    }
    // Updates the score of each of the players by summing up the discard piles
    for (shared_ptr<Player> player : players) {
        player->updateScore();
    }
    roundover = true;
    return true;
}

bool Board::gameOver() {
    // Iterates through all the players and returns true if one of the players has >= 80 points
    for (unsigned int i = 0; i < players.size(); i++) {
        if (players.at(i)->getScore() >= 80) {
            // Makes sure that if the game is already over, we don't print the message again
            if (!gameover) {
                notify(State::ENDGAME);
            }
            gameover = true;
            return true;
        }
    }
    return false;
}

bool Board::firstMove() {
    return firstplay;
}
