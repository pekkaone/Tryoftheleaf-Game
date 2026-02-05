#include <iostream>
#include "Game_Engine.h"

int main()
{

    Game_Engine game;

    while (game.Running())
    {
        game.update();

        game.render();
    }
    return 0;
}