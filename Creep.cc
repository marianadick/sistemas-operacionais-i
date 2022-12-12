#include "header-files/Creep.h"

__BEGIN_API

int Creep::_ATTACK_DELAY = 50;

Creep::Creep(Point point, Vector vector, std::shared_ptr<Sprite> creepSprite, ALLEGRO_COLOR color,
						 Launcher * launcher) : Enemy(point, vector, 1) {

  _creepSprite = creepSprite;
  _launcher = launcher;
  _color = color;

  initializeTimer();
}

Creep::~Creep() {
  if (_launcher != nullptr)
	_launcher->removeCreep(this);
}

void Creep::initializeTimer() {
  _attackDelayTimer = std::make_shared<Timer>(60);
  _attackDelayTimer->create();
  _attackDelayTimer->startTimer();
}

void Creep::draw()
{
	_creepSprite->draw_tinted(_point, _color, 0);
}

void Creep::update(double dt) {
  _point = _point + _speed * dt;
  if (_attackDelayTimer->getCount() > _ATTACK_DELAY) {
	_fire = true;
	_attackDelayTimer->srsTimer();
  }
}

void Creep::attack() 
{
  _fire = false;
}

ALLEGRO_COLOR Creep::getColor() 
{
  return _color;
}

int Creep::getSize() {
  return 20;
}

bool Creep::getFire() {
  return _fire;
}

bool Creep::isOutOfBounds() {
  return _point.x < -40;
}

__END_API