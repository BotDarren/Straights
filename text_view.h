#ifndef TEXT_VIEW_H
#define TEXT_VIEW_H
#include "controller.h"
#include "board.h"
#include "observer.h"
#include <string>

class View : public Observer {
    // The model for this view, this will be the subject
    Board *model;
    // The controller, this is used for the view to control the model
    Controller *controller;
public:
    // Processes input: gets the next command
    void nextCommand();
    // Constructor for the view given the controller and the model
    View (Controller *controller, Board *model);
    // Destructor for the view
    virtual ~View();
    // Sets the players: used in the beginning of the game
    void setPlayers();
    // Updates the view with the given state
    virtual void update(State state);
    // Prints the table as indicated in the project outline
    // Prints the current cards on the table and the hand and legal moves of current player
    void printTable();
    // Prints the deck: with 13 cards per line
    void printDeck();
};

#endif
