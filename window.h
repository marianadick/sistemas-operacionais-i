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
        void join();
        static void drawWindow();

        static Thread * _windowThread;
    protected:
    private:
};

__END_API

#endif