#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

// This was based largely upon the subject file from A4

class Observer;

class Subject {
    std::vector<Observer*> observers;

  public:
    // Attach observer
    void attach(Observer *o);
    // Detach observer
    void detach(Observer *o); 
    // Notify observers of a change 
    void notifyObservers();
};

#endif