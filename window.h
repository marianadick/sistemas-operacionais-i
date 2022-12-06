#ifndef window_h
#define window_h

#include "traits.h"
#include "thread.h"
#include "cpu.h"

#include "Point.h"
#include "Engine.h"

__BEGIN_API

class Window
{
    public:
        /* Methods */
        Window();
        ~Window();
        static void drawWindow();
        void join();

        /* Attributes */
        static Thread * _windowThread;
        static int * _row;
        static int * _col;
        static Point * _centre;
    protected:
    private:
};

__END_API

#endif