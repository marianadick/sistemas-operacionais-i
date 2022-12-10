#ifndef INPUT_H
#define INPUT_H

#include "traits.h"
#include "thread.h"
#include "cpu.h"
#include <iostream>

#include <allegro5/allegro.h>
#include "config.h"
#include "Action.h"
#include "Vector.h"
#include "Sprite.h"
#include "ship.h"

__BEGIN_API

class Input
{
    public:
        Input();
        ~Input();

        void runInput();
        bool checkPressedKey(act::action key);

    protected:
    private:    
        ALLEGRO_KEYBOARD_STATE _kb;
        ALLEGRO_EVENT_QUEUE *_eventQueue; // store inputs
};

__END_API

#endif