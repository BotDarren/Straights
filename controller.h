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

class Board;
class Player;
enum class PlayerType;

class Controller {
    // Pointer to the model
    Board *model;
public:
    Controller( Board* model );
    // Starts the game
    void startGame();
    // Plays a new round of the current game: assuming that the game has not ended
    void nextRound();
    // Add a player with the given type
    void addPlayer( PlayerType type );
    // Quits the current game: cleanup so no leakage
    void endGame();
    // Happens when a player chooses to rage quit: the human is replaced with a computer
    void RageQuit();
    // Sets the seed for the shuffling
    void setSeed( int seed );
    // Plays the given card: this is used by a human
    void makeMove(Card c = Card(Ace,Spade), bool mtype = true);
};

#endif
