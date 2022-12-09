#include "header-files/ship.h"

__BEGIN_API

const int PLAYER_SIZE = 16; // in pixels
const int PLAYER_TRAVEL_SPEED = 250;
const float MAX_LIFE = 3;

Thread * Ship::_shipThread;

Ship::Ship(Point p, ALLEGRO_COLOR c) : centre(p), color(c), speed(Vector(0, 0)),
					   lives(3), row(0), col(0), dead(false)
{
    Ship * _ship = this;
    db<System>(TRC) << ">> Thread Ship is initializing...\n";
    _shipThread = new Thread(Ship::run, _ship);
}

Ship::~Ship()
{
}

void Ship::run(Ship * _ship)
{}

void Ship::join()
{
    if (_shipThread) {
        _shipThread->join();
        //_shipThread->yield();
    }
    else
        db<CPU>(ERR) << ">> Unnable to join Thread Ship.\n";
}

void Ship::draw(std::shared_ptr<Sprite> sprite, int flags) 
{   
   sprite->draw_region(row, col, 47.0, 40.0, centre, flags);
   drawLives();
}

void Ship::update(double dt) 
{
   centre = centre + speed * dt;
   selectShipAnimation();
   speed = Vector(0, 0);
   checkBoundary();
}

void Ship::selectShipAnimation() 
{
   if (speed.x > 0) {
      col = 1;
      if (speed.y > 0) row = 2;
      else if (speed.y < 0) row = 0;
      else row = 1;
   } else {
      col = 0;
      if (speed.y > 0) row = 2;
      else if (speed.y < 0) row = 0;
      else row = 1;
   }
}

void Ship::checkBoundary() 
{   
   // check x bound and adjust if out
   if (centre.x > 800 - PLAYER_SIZE)
      centre.x = 800 - PLAYER_SIZE;
   else if (centre.x < PLAYER_SIZE)
      centre.x = PLAYER_SIZE;   
   // check y bound and adjust if out
   if (centre.y > 600 - PLAYER_SIZE)
      centre.y = 600 - PLAYER_SIZE;
   else if (centre.y < PLAYER_SIZE)
      centre.y = PLAYER_SIZE;
}

void Ship::drawLives()
{   
   al_draw_line(centre.x - PLAYER_SIZE*2, centre.y + PLAYER_SIZE*2,
		(centre.x - PLAYER_SIZE*2) + (lives / MAX_LIFE) * (PLAYER_SIZE*4),
		centre.y + PLAYER_SIZE*2,
		al_map_rgb(255 * (1.0 - lives / MAX_LIFE),
			   200 * (lives / MAX_LIFE),
			   0), 5);
}

__END_API