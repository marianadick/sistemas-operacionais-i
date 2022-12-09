#include "header-files/ship.h"

__BEGIN_API

int Ship::SHIP_SPEED = 250;
ALLEGRO_COLOR Ship::SHIP_COLOR = al_map_rgb(150, 0, 0);

Ship::Ship(Input * kb) : _kb(kb)
{
   loadSprites();
}

Ship::~Ship()
{
}

void Ship::runShip()
{
   while (*_gameRunning) {
		if (_window == nullptr)
			Thread::yield();

		getInputKb();
		Thread::yield();
	}
}

void Ship::getInputKb() {
   /* TO DO
	if (_kb == nullptr)
		return;
	if (_kb->getKbKeyIsPressed(KbKey::MOVE_UP))
		speed.y -= PlayerShip::PLAYER_TRAVEL_SPEED;
	if (_kb->getKbKeyIsPressed(KbKey::MOVE_DOWN))
		speed.y += PlayerShip::PLAYER_TRAVEL_SPEED;
	if (_kb->getKbKeyIsPressed(KbKey::MOVE_LEFT))
		speed.x -= PlayerShip::PLAYER_TRAVEL_SPEED;
	if (_kb->getKbKeyIsPressed(KbKey::MOVE_RIGHT))
		speed.x += PlayerShip::PLAYER_TRAVEL_SPEED;
	if (_kb->getKbKeyIsPressed(KbKey::NUM_1))
	if (_kb->getKbKeyIsPressed(KbKey::SPACE))
   */
}

void Ship::loadSprites() {
   _position = Point(215, 245);
   _speed = Vector(0, 0);

   // Go to resources directory
	ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, "resources");
	al_change_directory(al_path_cstr(path, '/'));

	// sprites
	_sprite = std::make_shared<Sprite>("Sprite2.png");

	// delete path
	al_destroy_path(path);
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

void Ship::attachWindow(Window * window)
{
   _window = window;
}

__END_API