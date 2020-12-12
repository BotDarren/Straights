#include "board.h"
#include "controller.h"
#include "text_view.h"

int main( int argc, char * argv[] ) {
    Board model; // Create model 
    Controller controller( &model );        // Create controller
    View       view( &controller, &model ); // Create the view -- is passed handle to controller and model.
    
    // If there is a seed that is provided, then we set the seed to
    // be the given seed
    if (argc == 1) {
        controller.setSeed(argv[0]); // FIX
    }
} 
