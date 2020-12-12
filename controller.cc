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

void Controller::addPlayer( PlayerType type ) {
    model->addPlayer(type);
}

void Controller::endGame() {
    //TO DO
}

shared_ptr<Player> Controller::RageQuit() {
    model->rage();
}

void Controller::printDeck( Player &player ) {
    model->printDeck();
}

void Controller::setSeed( int seed ) {
    model->setSeed(seed);
}
