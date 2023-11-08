
#include <iostream>
#include "Game.h"

int main()
{   

    //Init Game
    Game game;


    // Game loop
    while (game.running()) {

        

        // Update
        game.Update();


        // Render
        game.Render();


    }
    // End of my app
    return 0;
}