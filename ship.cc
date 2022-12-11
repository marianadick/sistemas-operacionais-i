#include "header-files/ship.h"
#include "header-files/configs.h"

__BEGIN_API

int Ship::SHIP_SPEED = 250;
int Ship::SHIP_SIZE = 16;
ALLEGRO_COLOR Ship::SHIP_COLOR = al_map_rgb(150, 0, 0);

Ship::Ship(Input * kb) :
            _kb(kb)
{
   init();
   db<System>(TRC) << ">> Player ship is initializing...\n";
   loadSprites();
}

Ship::~Ship()
{
   _sprite.reset();
   db<System>(TRC) << ">> Player ship destroyed...\n";
}

void Ship::runShip()
{
   while (Configs::_isGameRunning) {
		if (_window == nullptr)
			Thread::yield();

		getInputKb();
		Thread::yield();
	}
}

void Ship::getInputKb() {
	if (_kb != nullptr) {
      if (_kb->checkPressedKey(act::action::MOVE_UP))
         _speed.y -= Ship::SHIP_SPEED;
      if (_kb->checkPressedKey(act::action::MOVE_DOWN))
         _speed.y += Ship::SHIP_SPEED;
      if (_kb->checkPressedKey(act::action::MOVE_LEFT))
         _speed.x -= Ship::SHIP_SPEED;
      if (_kb->checkPressedKey(act::action::MOVE_RIGHT))
         _speed.x += Ship::SHIP_SPEED;
      if (_kb->checkPressedKey(act::action::FIRE_PRIMARY))
         {shootProjectile();}
      if (_kb->checkPressedKey(act::action::FIRE_SECONDARY))
         {} /* TO DO */
   }
}

void Ship::loadSprites() {
   _position = Point(200, 300);
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

void Ship::update(double dt) 
{
   _position = _position + _speed * dt;
   selectShipAnimation();
   _speed = Vector(0, 0);
   checkBoundary();
}

void Ship::draw() 
{   
   Point centre = _position;
   _sprite->draw_region(_row, _col, 47.0, 40.0, centre, 0);
}


void Ship::selectShipAnimation() 
{
   if (_speed.x > 0) {
      _col = 1;
      if (_speed.y > 0) _row = 2;
      else if (_speed.y < 0) _row = 0;
      else _row = 1;
   } else {
      _col = 0;
      if (_speed.y > 0) _row = 2;
      else if (_speed.y < 0) _row = 0;
      else _row = 1;
   }
}

void Ship::checkBoundary() 
{   
   // check x bound and adjust if out
   if (_position.x > 800 - SHIP_SIZE)
      _position.x = 800 - SHIP_SIZE;
   else if (_position.x < SHIP_SIZE)
      _position.x = SHIP_SIZE;   
   // check y bound and adjust if out
   if (_position.y > 600 - SHIP_SIZE)
      _position.y = 600 - SHIP_SIZE;
   else if (_position.y < SHIP_SIZE)
      _position.y = SHIP_SIZE;
}

void Ship::shootProjectile() 
{
   if (this->laserTimer->getCount() > 8)
	{
      Laser *laserToShot = new Laser(_position, SHIP_COLOR, Vector(500, 0), true);
		this->laserTimer->srsTimer();
		// Coloca referência do tiro na classe Collision e Window
		this->_window->addDrawableItem(laserToShot);
	};
}

void Ship::init()
{
	// Create the timers for the weapons
	this->laserTimer = std::make_shared<Timer>(60);
	this->laserTimer->create();
	this->laserTimer->startTimer();
}
void Ship::attachWindow(Window * window)
{
   _window = window;
}

void Ship::attachCollision(Collision * collision)
{
   _collision = collision;
}

void Ship::hit(int damage)
{
	if (this->wasShot)
		return;

	this->life -= damage;
	this->wasShot = true;
}

int Ship::getSize() { return Ship::SHIP_SIZE; }

Point Ship::getPosition() { return this->_position; }


__END_API