#ifndef _OBSERVER_H_
#define _OBSERVER_H_

// Based largely on the observer.h from the mvc lectures

class Subject;

class Observer {
  public:
    // Used to update the observers: State indicates the state of the game
    virtual void update (State State) = 0;
};

#endif
