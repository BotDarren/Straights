/*
 * MVC example of GTKmm program
 *
 * Controller class.  Is responsible for translating UI events (from the View)
 * into method calls to the Model.
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Updated to GTKmm 3.0 (version 3.10.1) from 2.4 on February 13, 2017.
 *  Copyright 2009, 2017 UW. All rights reserved.
 *
 */

#include "controller.h"
#include <memory>
using namespace std;

Controller::Controller( Board* model ) : model{model} {}

void Controller::startGame() {
    model->start();
}

void Controller::nextRound() {
    model->nextRound();
}

void Controller::addPlayer( PlayerType type ) {
    model->addPlayer(type);
}

void Controller::endGame() {
    throw ArgExn("Game Over. Game ended by user");
}

void Controller::RageQuit() {
    model->rage();
}

void Controller::setSeed( unsigned int seed ) {
    model->setSeed(seed);
}

void Controller::makeMove(Card c, bool mtype) {
    // The mtype represents the type of move: true = play, false = discard
    model->makeMove(c, mtype);
}

vector<shared_ptr<Player>> Controller::getPlayers() const {
    return model->getPlayers();
}

int Controller::getCurrentPlayer() const {
    return model->getCurrentPlayer();
}

shared_ptr<Card> Controller::topCard() const {
    return model->topCard();
}

shared_ptr<Card> Controller::topDiscard() const {
    return model->topDiscard();
}

vector<shared_ptr<Card>> Controller::getPlayed() const {
    return model->getPlayed();
}

vector<shared_ptr<Card>> Controller::getHand() const {
    return model->getHand();
}

vector<shared_ptr<Card>> Controller::getValidPlays() const {
    return model->getValidPlays();
}

vector<shared_ptr<Card>> Controller::getDeck() const {
    return model->getDeck();
}
