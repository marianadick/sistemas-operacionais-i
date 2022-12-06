#ifndef game_h
#define game_h

#include <iostream>
#include "cpu.h"
#include "traits.h"
#include "thread.h"
#include "semaphore.h"

#include "Engine.h"
#include "window.h"

__BEGIN_API

class Game
{
public:
    Game();
    
    ~Game();

    static void run();

    static Window * _window;
    static Engine * _engine;

    static Thread * _gameThread;
};

__END_API

#endif
