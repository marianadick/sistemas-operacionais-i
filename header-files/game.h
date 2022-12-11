#ifndef game_h
#define game_h

#include <iostream>
#include "cpu.h"
#include "traits.h"
#include "thread.h"

#include "window.h"
#include "input.h"
#include "ship.h"
#include "configs.h"
#include "enemyGroupPurple.h"

__BEGIN_API

class Game
{
public:
    Game() {};
    ~Game() {};

    static void gameRun(void *name) {
        db<System>(TRC) << ">> Game is starting...\n";

        _windowThread = new Thread(windowRun);
        _kbThread = new Thread(kbRun);
        _shipThread = new Thread(shipRun);
        
        _shipThread->join();
        _windowThread->join();
        _kbThread->join();

        delete _shipThread;
        delete _windowThread;
        delete _kbThread;

        db<System>(TRC) << ">> Game is ending...\n";
    };

private:
    static Thread * _windowThread;
    static Thread * _shipThread;
    static Thread * _kbThread;

    static Window * _window;
    static Ship * _ship;
    static Input * _kb;

    static EnemyGroupPurple * _enemyGroupPurple;

    /* WINDOW */
    static void windowRun() {
        _window = new Window(Configs::_widthDisplay, Configs::_heightDisplay, Configs::_fps);
        _window->runWindow();
        delete _window;
    };

    /* SHIP */
    static void shipRun() {
        _ship = new Ship(_kb);
        // Window gets the Ship reference and the same ocurres for the Ship
        _window->attachShip(_ship); _ship->attachWindow(_window);
        _ship->runShip();
        delete _ship;
    };

    /* INPUT */
    static void kbRun() {
        _kb = new Input();
        _kb->runInput();
        delete _kb;
    };
};

__END_API

#endif
