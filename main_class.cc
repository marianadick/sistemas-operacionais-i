#include "main_class.h"

__BEGIN_API

void MainClass::runGame(void * name) {
    db<System>(TRC) << ">> Thread main is starting the game...\n";
    srand(time(0));
    Engine shooty(800, 600, 60);
    shooty.init();
    shooty.run();
}

__END_API
