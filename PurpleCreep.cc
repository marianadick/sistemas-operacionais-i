#include "header-files/PurpleCreep.h"

__BEGIN_API

int PurpleCreep::_SHOTS_DELAY = 50;

PurpleCreep::PurpleCreep(Point point, Vector vector, std::shared_ptr<Sprite> shipSprite,
						 std::shared_ptr<Sprite> deathSprite, PurpleCreepLauncher *purpleCreepLauncher) : Enemy(point,
																												vector,
																												1) {
  _shipSprite = shipSprite;
  _deathSprite = deathSprite;

  _purpleCreepLauncher = purpleCreepLauncher;

  _color = al_map_rgb(150, 0, 150);
  _deathSpriteTimer = 5;

  initializeTimer();
}

PurpleCreep::~PurpleCreep() {
  if (_purpleCreepLauncher != nullptr)
	_purpleCreepLauncher->removeShip(this);
}

void PurpleCreep::initializeTimer() {
  _shotsTimer = std::make_shared<Timer>(60);
  _shotsTimer->create();
  _shotsTimer->startTimer();
}

void PurpleCreep::draw() {
  if (getDead()) {
	_deathSpriteTimer -= 1;
	_deathSprite->draw_death_anim(_deathSpriteTimer, _point, 0);
  } else {
	_shipSprite->draw_tinted(_point, _color, 0);
  }
}

void PurpleCreep::update(double dt) {
  _point = _point + _speed * dt;
  // Added some random delay
  if (_shotsTimer->getCount() > PurpleCreep::_SHOTS_DELAY + rand() % 60) {
	_fire = true;
	_shotsTimer->srsTimer();
  }
}

void PurpleCreep::attack() {
  _fire = false;
}

ALLEGRO_COLOR PurpleCreep::getColor() {
  return _color;
}

int PurpleCreep::getSize() {
  return 20;
}

bool PurpleCreep::setFire() {
  return _fire;
}

bool PurpleCreep::isOutOfBounds() {
  return _point.x < -40;
}

__END_API