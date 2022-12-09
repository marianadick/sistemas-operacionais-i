#ifndef ship_h
#define ship_h

#include "traits.h"
#include "thread.h"

#include "Point.h"
#include "Vector.h"
#include "Sprite.h"
#include "Action.h"
#include <memory>

#include "configs.h"
#include "input.h"
#include "window.h"

__BEGIN_API
class Window;

class Ship
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
        void selectShipAnimation();
        void checkBoundary();
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

};

__END_API

#endif