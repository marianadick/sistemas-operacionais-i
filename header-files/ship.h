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
#include "hittable.h"
#include "Timer.h"
#include "CollisionHandler.h"

__BEGIN_API
//class Window;
class CollisionHandler;

class Ship : public Hittable
{
    public:
        Ship();
        Ship(Input * kb);
        ~Ship();

        void runShip();
        void getInputKb();
        void hit(int damage);
        int getSize();
        Point getPosition();
        bool isDead();
        bool isOutOfBounds();

        void draw();
        void update(double dt);

        void attachWindow(Window * window);
        void attachCollision(CollisionHandler * colision);
        
    protected:
    private:
        void init();
        void selectShipAnimation();
        void checkBoundary();
        void shootProjectile();
        void loadSprites();
		void drawLives();
        
	    static int SHIP_SPEED;
        static int SHIP_SIZE;
		static int LASER_DELAY;
    	static ALLEGRO_COLOR SHIP_COLOR;

        /* Ship position */
        int life = 3;
        bool wasShot = false;
	    int _row;			/**<row of animation to be played */
	    int _col;			/**< column of animation to be played */
        Point _position;
        Vector _speed;
        std::shared_ptr<Sprite> _sprite;

        /* Reference to game state and obj*/
        Input * _kb;
        Window * _window;
        CollisionHandler * _collision;

        std::shared_ptr<Timer> laserTimer;

};

__END_API

#endif