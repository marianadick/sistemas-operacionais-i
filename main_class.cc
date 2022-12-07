#include "main_class.h"

__BEGIN_API

void MainClass::runGame(void * name) {
    Game * game = new Game(800, 600, 60);
    delete game;
}

__END_API
