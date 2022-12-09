#ifndef ship_h
#define ship_h

#include "traits.h"
#include "thread.h"

#include "Point.h"
#include "Vector.h"
#include "Sprite.h"
#include "Action.h"
#include <memory>

#include "input.h"
#include "window.h"

__BEGIN_API

class Ship
{
    public:
        Ship(Input * kb);
        ~Ship();

        void runShip();
        void update(double dt);
        void getInputKb();

        //void draw(std::shared_ptr<Sprite> sprite, int flags);

        void attachWindow(Window * window);
        
    protected:
    private:
        void loadSprites();
        
	    static int SHIP_SPEED;
    	static ALLEGRO_COLOR SHIP_COLOR;

        Point * _position;
        Vector * _speed;
        std::shared_ptr<Sprite> _sprite;

        /* Reference to game state and obj*/
        bool * _gameRunning;
        Input * _kb;
        Window * _window;

};

__END_API

#endif