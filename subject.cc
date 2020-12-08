#include "subject.h"
#include "observer.h"
#include <vector>
#include <algorithm>

void Subject::attach(Observer *o) { observers.emplace_back(o); }

void Subject::detach(Observer *o) {
    for (int i = 0; i < observers.size(); i++) {
        if (observers.at(i) == o) {
            observers.erase(observers.begin() + i);
        }
    }
}

void Subject::notifyObservers() {
    for (auto &ob : observers) ob->notify( *this );
}
