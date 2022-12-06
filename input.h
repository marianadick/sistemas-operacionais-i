#ifndef input_h
#define input_h

#include "traits.h"
#include "thread.h"
#include "cpu.h"

#include <allegro5/allegro.h>

__BEGIN_API

class Input
{
    public:
        Input();

        ~Input();
        static void join();
        static void getKey();

        static Thread * _inputThread;        
    protected:
    private:
};

__END_API

#endif