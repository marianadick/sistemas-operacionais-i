#ifndef game_h
#define game_h

#include <iostream>
#include "cpu.h"
#include "thread.h"
#include "traits.h"

#include "window.h"
#include "configs.h"
#include "input.h"
#include "ship.h"
#include "CollisionHandler.h"
#include "PurpleCreepLauncher.h"

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
        _collisionThread = new Thread(collisionRun);
        _enemyGroupPurpleThread = new Thread(enemyGroupPurpleRun);
        
        _kbThread->join();
        _shipThread->join();
        _windowThread->join();
        _collisionThread->join();
        _enemyGroupPurpleThread->join();

        delete _shipThread;
        delete _windowThread;
        delete _kbThread;
        delete _collisionThread;
        delete _enemyGroupPurpleThread;

        db<System>(TRC) << ">> Game is ending...\n";
    };

private:
    static Thread * _windowThread;
    static Thread * _shipThread;
    static Thread * _kbThread;
    static Thread * _enemyGroupPurpleThread;
    static Thread * _collisionThread;

    static Window * _window;
    static Ship * _ship;
    static Input * _kb;
    static CollisionHandler * _collision;
    static PurpleCreepLauncher * _enemyGroupPurple;

    /* WINDOW */
    static void windowRun() {
        _window = new Window(Configs::_widthDisplay, Configs::_heightDisplay, Configs::_fps);
        _window->runWindow();
        delete _window;
        _windowThread->thread_exit(2);
    };

    /* SHIP */
    static void shipRun() {
        _ship = new Ship(_kb);
        // Window gets the Ship reference and the same ocurres for the Ship
        _window->attachShip(_ship); _ship->attachWindow(_window);
        _ship->runShip();
        delete _ship;
        _shipThread->thread_exit(3);
    };

    /* INPUT */
    static void kbRun() {
        _kb = new Input();
        _window->attachKb(_kb);
        _kb->runInput();
        delete _kb;
        _kbThread->thread_exit(4);
    };

    /* ENEMY GROUP PURPLE */
    static void enemyGroupPurpleRun() {
        _enemyGroupPurple = new PurpleCreepLauncher();
	    _enemyGroupPurple->attachCollision(_collision);
	    _enemyGroupPurple->attachWindow(_window);
        _enemyGroupPurple->run();
        delete _enemyGroupPurple;
        _enemyGroupPurpleThread->thread_exit(5);

    };

    /* COLLISION */
    static void collisionRun() {
        _collision = new CollisionHandler();
        _collision->attachShip(_ship);
        _collision->attachWindow(_window);
        _ship->attachCollision(_collision);
        _collision->runCollision();
        delete _collision;
        //_collisionThread->thread_exit(6);
    };
};

__END_API

#endif
