#include "Game_Engine.h"

int main()
{
    std::srand(static_cast<unsigned>(time(NULL)));

    Game_Engine game;

    while (game.Running())
    {
        game.update();

        game.render();
    }
    return 0;
}