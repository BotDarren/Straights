#include "computer.h"
#include "move.h"
#include "player.h"
#include "board.h"
using namespace std;

Computer::Computer(Board *model) : Player{PlayerType::Computer,model} {}

Move Computer::play() {
    Move tmp{};
    vector<shared_ptr<Card>> validmoves = getValidPlays();
    if (validmoves.size() > 0) {
        tmp.setType(MoveType::Play);
    } else {
        tmp.setType(MoveType::Discard);
    }
    tmp.setCard(*(hand.at(0)));
}
