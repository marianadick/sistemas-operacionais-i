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
#include "WhiteCreepLauncher.h"
#include "CreepBombLauncher.h"

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
        _enemyGroupWhiteThread = new Thread(enemyGroupWhiteRun);
        _creepBombLauncherThread = new Thread(creepBombRun);
        
        _kbThread->join();
        _shipThread->join();
        _windowThread->join();
        _collisionThread->join();
        _enemyGroupPurpleThread->join();
        _enemyGroupWhiteThread->join();
        _creepBombLauncherThread->join();

        delete _shipThread;
        delete _windowThread;
        delete _kbThread;
        delete _collisionThread;
        delete _enemyGroupPurpleThread;
        delete _enemyGroupWhiteThread;
        delete _creepBombLauncherThread;

        db<System>(TRC) << ">> Game is ending...\n";
    };

private:
    /* THREADS */
    static Thread * _windowThread;
    static Thread * _shipThread;
    static Thread * _kbThread;
    static Thread * _enemyGroupPurpleThread;
    static Thread * _enemyGroupWhiteThread;
    static Thread * _collisionThread;
    static Thread * _creepBombLauncherThread;

    /* GAME OBJECTS */
    static Window * _window;
    static Ship * _ship;
    static Input * _kb;
    static CollisionHandler * _collision;
    static PurpleCreepLauncher * _enemyGroupPurple;
    static WhiteCreepLauncher * _enemyGroupWhite;
    static CreepBombLauncher * _creepBombLauncher;

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
        _window->attachShip(_ship); 
        _ship->attachWindow(_window);
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
        _enemyGroupPurple->runLauncher();
        delete _enemyGroupPurple;
        _enemyGroupPurpleThread->thread_exit(5);

    };

    /* ENEMY GROUP WHITE */
    static void enemyGroupWhiteRun() {
        _enemyGroupWhite = new WhiteCreepLauncher();
	    _enemyGroupWhite->attachCollision(_collision);
	    _enemyGroupWhite->attachWindow(_window);
        _enemyGroupWhite->runLauncher();
        delete _enemyGroupWhite;
        _enemyGroupWhiteThread->thread_exit(6);

    };

    /* COLLISION */
    static void collisionRun() {
        _collision = new CollisionHandler();
        _collision->attachShip(_ship);
        _collision->attachWindow(_window);
        _ship->attachCollision(_collision);
        _collision->runCollision();
        delete _collision;
    };

    /* CREEP BOMB RUN */
    static void creepBombRun() {
        _creepBombLauncher = new CreepBombLauncher();
        _creepBombLauncher->setCollisionHandlerReference(_collision);
        _creepBombLauncher->setWindowReference(_window);
        _creepBombLauncher->runCreepBombLauncher();
        delete _creepBombLauncher;
        _creepBombLauncherThread->thread_exit(7);
    }
};

__END_API

#endif
