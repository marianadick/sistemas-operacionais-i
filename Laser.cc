#include <allegro5/allegro_primitives.h>
#include "header-files/Laser.h"

__BEGIN_API

Laser::Laser(Point point, ALLEGRO_COLOR color, Vector speed, bool isPlayerShot) : Projectile(point, color, speed, isPlayerShot)
{
    hitUntilDestroyed = 1;
}

Laser::~Laser() {}

void Laser::draw()
{
    Point otherPoint = _point + _speed * (0.05);
    al_draw_line(_point.x, _point.y, otherPoint.x, otherPoint.y, _color, 3);
}

void Laser::update(double diffTime)
{
    _point = _point + _speed * diffTime;
}

int Laser::getSize() { 
    return 3; 
}

void Laser::ackHitSomething() {
     hitUntilDestroyed -= 1; 
}

bool Laser::wasDestroyed() {
     return hitUntilDestroyed == 0; 
}

int Laser::getDamage() {
     return 1; 
}

__END_API