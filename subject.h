#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

// This was based largely upon the subject file from mvc example

class Observer;

class Subject {
    std::vector<Observer*> observers;

  public:
    // Attach observer
    void attach( Observer *o );
    // Detach observer
    void detach( Observer *o ); 
  protected:
    // Notify observers of a change 
    void notify();
};

#endif
