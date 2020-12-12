#include "text_view.h"
using namespace std;

View::View (Controller *controller, Board *model) : controller{controller}, model{model} {
    model->attach(this);
}

View::~View() {

}

void View::update() {

}

string inputCard() {

}
