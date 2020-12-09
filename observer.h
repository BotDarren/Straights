#ifndef _OBSERVER_H_
#define _OBSERVER_H_

// Based largely on the observer.h from the mvc lectures

class Subject;

class Observer {
  public:
    // Used to update the observers
    virtual void update () = 0;
};

#endif
