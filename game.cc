#include "game.h"

__BEGIN_API

Window * Game::_window;
Engine * Game::_engine;

Game::Game() {
    
    _engine = new Engine(800, 600, 60);

    _window = new Window();
    _window->join();
    run();
}

Game::~Game() {
    delete _engine;
    //delete _window;
}

void Game::run() {
    db<System>(TRC) << ">> Thread Game is starting...\n";
    
    srand(time(0));
    float prevTime = 0;
    bool finish = false;

    _engine->init();
    while (1) {
        if (!_engine->gameLoop(prevTime)) {
            finish = true;
            break;
        }
    };
}

__END_API
