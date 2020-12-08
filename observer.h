#ifndef _OBSERVER_H_
#define _OBSERVER_H_

// Based largely on the observer.h from A4

class Subject;

class Observer {
  public:
    // Pass in the Subject that called the notify method.
    virtual void notify( Subject & whoNotified ) = 0;

    virtual ~Observer() = default;
};

#endif
