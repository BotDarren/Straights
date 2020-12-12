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
    // Processes input
    void nextCommand();
public:
    // Constructor for the view given the controller and the model
    View (Controller *controller, Board *model);
    // Destructor for the view
    virtual ~View();
    virtual void update();
    // Gets the card if the current command is a play/discard
    std::string inputCard();
};

#endif
