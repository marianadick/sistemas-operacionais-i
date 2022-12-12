#include "header-files/Laser.h"

__BEGIN_API

Laser::Laser(Point point, ALLEGRO_COLOR color, Vector speed, bool isPlayerShot) : Projectile(point, color, speed, isPlayerShot)
{
    _point = _point + speed * 0.1;
    _destroyed = false;
}

Laser::~Laser() {}

void Laser::draw()
{
    Point nextPos = _point + _speed * (0.05);
    al_draw_line(_point.x, _point.y, nextPos.x, nextPos.y, _color, 3);
}

void Laser::update(double dt)
{
    _point = _point + _speed * dt;
}

int Laser::getSize() { 
    return 4; 
}

bool Laser::wasDestroyed() {
     return _destroyed; 
}

int Laser::getDamage() {
     return 1; 
}

void Laser::ackHitSomething() {
     _destroyed = true; 
}

__END_API