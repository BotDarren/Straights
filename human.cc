#include <
#include "human.h"
#include "move.h"
#include "player.h"
#include "board.h"
using namespace std;

Human::Human(Board *model) : Player{PlayerType::Human,model} {}

Move Human::play() {
    Move tmp{};
    vector<shared_ptr<Card>> validmoves = getValidPlays();
    if (validmoves.size() > 0) {
        tmp.setType(MoveType::Play);
    } else {
        tmp.setType(MoveType::Discard);
    }
    // Either find someway to make the move or read input
    // PENDING PIAZZA POST
}
