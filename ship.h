#ifndef ship_h
#define ship_h

#include "traits.h"
#include "thread.h"
#include "cpu.h"
#include "ship.h"
#include "Point.h"
#include "Vector.h"
#include "Sprite.h"
#include "Action.h"
#include <allegro5/allegro_primitives.h>
#include <memory>


//#include "Vector.h"

__BEGIN_API

class Ship
{
    public:
        Point centre;        /**< ship position */
        ALLEGRO_COLOR color; /**< ship color */
   
        Vector speed;        /**< movement speed in any direction */
        float lives;         /**< lives remaining of Player object before destroyed */
        int row;             /**<row of animation to be played */
        int col;             /**< column of animation to be played */
        bool dead;           /**< signals Player object has been killed */

        Ship(Point p, ALLEGRO_COLOR c);
        ~Ship();
        static void run(Ship * _ship);
        void join();
        void draw(std::shared_ptr<Sprite> sprite, int flags);
        void update(double dt);
        static Thread * _shipThread;
        
    protected:
    private:
        void drawLives();
        void checkBoundary();
        void update();
        void selectShipAnimation();

};

__END_API

#endif