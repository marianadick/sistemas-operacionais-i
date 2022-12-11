#include "header-files/ship.h"

__BEGIN_API

int Ship::SHIP_SPEED = 250;
int Ship::SHIP_SIZE = 16;
int Ship::LASER_DELAY = 6;
int Ship::MISSILE_DELAY = 20;

ALLEGRO_COLOR Ship::SHIP_COLOR = al_map_rgb(0, 200, 0);

Ship::Ship() {
  db<System>(TRC) << ">> Player ship is initializing...\n";
  this->initializeTimers();
  loadSprites();
}

Ship::Ship(Input *kb) :
	_kb(kb) {
  db<System>(TRC) << ">> Player ship is initializing...\n";
  this->initializeTimers();
  loadSprites();
}

Ship::~Ship() {
  _sprite.reset();
  db<System>(TRC) << ">> Player ship destroyed...\n";
}

void Ship::runShip() {
  while (Configs::_isGameRunning) {
	if (_window == nullptr || _collision == nullptr)
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
	if (_kb->checkPressedKey(act::action::FIRE_PRIMARY)) { shootLaser(); }
	if (_kb->checkPressedKey(act::action::FIRE_SECONDARY)) { shootMissile(); }
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

void Ship::update(double dt) {
  _position = _position + _speed * dt;
  selectShipAnimation();
  _speed = Vector(0, 0);
  checkBoundary();
}

void Ship::draw() {
  Point centre = _position;
  _sprite->draw_region(_row, _col, 47.0, 40.0, centre, 0);
  drawHealthBar();
}

void Ship::selectShipAnimation() {
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

void Ship::checkBoundary() {
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

void Ship::shootLaser() {
  if (laserDelayTimer->getCount() > LASER_DELAY) {
    Laser * laser = new Laser(_position, SHIP_COLOR, Vector(500, 0), true);
    laserDelayTimer->srsTimer();
    _window->addProjectile(laser);
    _collision->newPlayerShot(laser);
  };
}

void Ship::shootMissile() {
  if (laserDelayTimer->getCount() > MISSILE_DELAY) {
	Missile * missile = new Missile(_position, SHIP_COLOR, Vector(500, 0), true);
	laserDelayTimer->srsTimer();
	_window->addProjectile(missile);
	_collision->newPlayerShot(missile);
  };
}

void Ship::initializeTimers() {
  laserDelayTimer = std::make_shared<Timer>(Configs::_fps);
  laserDelayTimer->create();
  laserDelayTimer->startTimer();

  missileDelayTimer = std::make_shared<Timer>(Configs::_fps);
	missileDelayTimer->create();
	missileDelayTimer->startTimer();
}

void Ship::attachWindow(Window *window) {
  _window = window;
}

void Ship::attachCollision(CollisionHandler *collision) {
  _collision = collision;
}

void Ship::hit(int damage) {
  _life -= damage;
  if (_life < 1)
      _dead = true;
}

int Ship::getSize() {
  return Ship::SHIP_SIZE;
}

Point Ship::getPosition() {
  return _position;
}

bool Ship::getDead() {
  return _dead;
}

int Ship::getShipLives() {
  return _life;
}

void Ship::drawHealthBar() {
  Point centre = _position;
  al_draw_line(centre.x - SHIP_SIZE * 2, centre.y + SHIP_SIZE * 2,
			   (centre.x - SHIP_SIZE * 2) + (_life / 3) * (SHIP_SIZE * 4),
			   centre.y + SHIP_SIZE * 2,
			   al_map_rgb(255 * (1.0 - _life / 3),
						  200 * (_life / 3),
						  0), 5);
}

__END_API