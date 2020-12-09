#ifndef TEXT_VIEW_H
#define TEXT_VIEW_H
#include "controller.h"
#include "board.h"
#include "observer.h"

class View : public Observer {
    Board *model;
    Controller *controller;
    // Processes input
    void nextCommand();
public:
    View (Controller *controller, Board *model);
    virtual ~View();
    virtual void update();
};

#endif
