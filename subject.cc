#include "subject.h"
#include "observer.h"
#include <vector>
#include <algorithm>

void Subject::attach(Observer *o) { observers.emplace_back(o); }

void Subject::detach(Observer *o) {
    // Iterates through the observers and erases them all
    for (unsigned int i = 0; i < observers.size(); i++) {
        if (observers.at(i) == o) {
            observers.erase(observers.begin() + i);
        }
    }
}

void Subject::notify(State state) {
    // Iterates through the observers and updates each of them
    for (auto &ob : observers) ob->update(state);
}
