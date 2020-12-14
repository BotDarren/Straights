#include <iostream>
#include <sstream>
#include "board.h"
#include "controller.h"
#include "text_view.h"

int main( int argc, char * argv[] ) {
    Board model; // Create model 
    Controller controller( &model );        // Create controller
    View       view( &controller, &model ); // Create the view -- is passed handle to controller and model.
    
    // If there are more than 2 arguments, then this is not a valid way to use this program
    if (argc > 2) {
        std::cerr << "Usage: straights <seed>" << std::endl;
        return 1;
    }
    // If there is a seed that is provided, then we set the seed to be the given seed
    if (argc == 2) {
        // This format of input is based on the main file from A5
        std::istringstream aiss{argv[1]};
        unsigned int seed;
        aiss >> seed;
        // Sets the seed to the provbided seed
        controller.setSeed(seed);
    }
    // Prompts the user to initate the player type
    view.setPlayers();
    // Starts the game
    controller.startGame();
    // If we quit then an exception is throw
    try {
        // We keep trying to get the next commands until the game is over
        while (!(model.gameOver())) {
            // If the round is over, then we initiate a new round
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
    } catch ( ArgExn & e ) {
            // Catches the event that an exception is thrown when the user quits
            cerr << e.message << endl;
            return 1;
    }
    return 0;
}
