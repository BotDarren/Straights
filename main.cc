#include <iostream>
#include <sstream>
#include "board.h"
#include "controller.h"
#include "text_view.h"

int main( int argc, char * argv[] ) {
    Board model; // Create model 
    Controller controller( &model );        // Create controller
    View       view( &controller, &model ); // Create the view -- is passed handle to controller and model.
    
    // If there is a seed that is provided, then we set the seed to be the given seed
    if (argc > 2) {
        std::cerr << "Usage: straights <seed>" << std::endl;
        return 1;
    }
    if (argc == 2) {
        std::istringstream aiss{argv[1]};
        unsigned int seed;
        aiss >> seed;
        controller.setSeed(seed);
    }
    view.setPlayers();
    controller.startGame();
    while (!(model.gameOver())) {
        if (!model.roundOver()) {
            if (model.getPlayerType() == PlayerType::Computer) {
                controller.makeMove();
            } else {
                view.nextCommand();
            }
        } else {
            controller.nextRound();
        }
    }
    return 0;
}
