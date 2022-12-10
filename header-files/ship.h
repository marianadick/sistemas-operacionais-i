#ifndef ship_h
#define ship_h

#include "thread.h"
#include "traits.h"
#include <memory>

#include "configs.h"
#include "input.h"
#include "window.h"

#include "Point.h"
#include "Vector.h"
#include "Sprite.h"
#include "Action.h"
#include "Laser.h"
#include "Drawable.h"
#include "Timer.h"

__BEGIN_API
class Window;

class Ship: public Drawable
{
    public:
        Ship(Input * kb);
        ~Ship();

        void runShip();
        void getInputKb();

        void draw();
        void update(double dt);

        void attachWindow(Window * window);
        
    protected:
    private:
        void init();
        void selectShipAnimation();
        void checkBoundary();
        void shootProjectile();
        void loadSprites();
        
	    static int SHIP_SPEED;
        static int SHIP_SIZE;
    	static ALLEGRO_COLOR SHIP_COLOR;

        /* Ship position */
	    int _row;			/**<row of animation to be played */
	    int _col;			/**< column of animation to be played */
        Point _position;
        Vector _speed;
        std::shared_ptr<Sprite> _sprite;

        /* Reference to game state and obj*/
        Input * _kb;
        Window * _window;

        std::shared_ptr<Timer> laserTimer;

};

__END_API

#endif