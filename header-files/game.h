#ifndef game_h
#define game_h

#include <iostream>
#include "cpu.h"
#include "traits.h"
#include "thread.h"

#include <stdexcept>

#include "window.h"
#include "ship.h"
#include "input.h"

__BEGIN_API

class Game
{
public:
    Game() {};
    ~Game() {};

    static void gameRun();
    
    /* Window display parameters*/
    static int _w;
    static int _h;
    static int _fps;
    static bool _isRunning; // if true, the game is running

private:
    /* SHIP */
    static void shipRun();
    static Thread * _shipThread;
    static Ship * _ship;

    /* WINDOW */
    static void windowRun(int w, int h, int fps,  bool * _gameRunning);
    static Thread * _windowThread;
    static Window * _window;

    /* INPUT */
    static void kbRun();
    static Thread * _kbThread;
    static Input * _kb;
};

__END_API

#endif
