#ifndef input_h
#define input_h

#include "traits.h"
#include "thread.h"
#include "cpu.h"
#include <iostream>

#include <allegro5/allegro.h>
#include "Action.h"

__BEGIN_API

class Input
{
    public:
        Input(act::action * actionPlayer);
        ~Input();

        void join();
        static void inputHandler(Input * _input);

        act::action * _actionPlayer;
        static Thread * _inputThread;
    protected:
    private:
};

__END_API

#endif