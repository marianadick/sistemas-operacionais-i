#ifndef ship_h
#define ship_h

#include "traits.h"
#include "thread.h"
#include "cpu.h"

//#include "Vector.h"

__BEGIN_API

class Ship
{
    public:
        Ship();
        ~Ship();
        static void join();
        static void selectShipAnimation();

        static Thread * _shipThread;
        //Vector *speed;
        
    protected:
    private:
};

__END_API

#endif