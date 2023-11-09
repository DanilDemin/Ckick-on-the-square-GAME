
#include <iostream>
#include "Game.h"

int main()
{   

    // Init srand
    std::srand(static_cast<unsigned>(time(NULL)));



    //Init Game engin
    Game game;


    // Game loop
    while (game.running() && !game.getEndGame()) {

        

        // Update
        game.Update();
        
         

        // Render
        game.Render();

    }
    // End of my app
    return 0;
}