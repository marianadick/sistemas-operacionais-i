#ifndef input_h
#define input_h

#include "traits.h"
#include "thread.h"
#include "cpu.h"
#include <iostream>

#include <allegro5/allegro.h>
#include "Action.h"
#include "Vector.h"

__BEGIN_API

class Input
{
    public:
        Input(act::action * actionPlayer, bool * finish, ALLEGRO_KEYBOARD_STATE *kb, Vector *speed);
        ~Input();

        void join();
        static void inputHandler(Input * _input);

        ALLEGRO_KEYBOARD_STATE *_kb;
        act::action * _actionPlayer;
        Vector *_speed;
        bool * _finish;
        static Thread * _inputThread;
    protected:
    private:
};

__END_API

#endif