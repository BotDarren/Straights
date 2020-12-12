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

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "board.h"
#include "player.h"
#include "deck.h"

class Controller {
    // Pointer to the view
    Board *model;
public:
    Controller( Board* model );
    // Starts the game
    void startGame();
    // Add a player with the given type
    void addPlayer( PlayerType type );
    // Quits the current game: cleanup so no leakage
    void endGame();
    // Happens when a player chooses to rage quit: the human is replaced with a computer
    std::shared_ptr<Player> RageQuit();
    // Prints the current deck of the player: 13 cards per line (not part of official game)
    void printDeck( Player &player );
    // Sets the seed for the shuffling
    void setSeed( int seed );
};

#endif
