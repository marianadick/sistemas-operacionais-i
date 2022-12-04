#ifndef window_h
#define window_h

#include "traits.h"
#include "thread.h"
#include "cpu.h"

__BEGIN_API

class Window
{
    public:
        Window();
        ~Window();

        static void drawWindow();

        static Thread * _windowThread;
    protected:
    private:
};

__END_API

#endif