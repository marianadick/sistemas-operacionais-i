#include <allegro5/allegro_primitives.h>
#include "header-files/Laser.h"

__BEGIN_API

Laser::Laser(Point point, ALLEGRO_COLOR color, Vector speed, bool isPlayerShot) : Projectile(point, color, speed, isPlayerShot)
{
    this->hitUntilDestroyed = 1;
}

Laser::~Laser() {}

void Laser::draw()
{
    Point otherPoint = this->_point + this->_speed * (0.05);
    al_draw_line(this->_point.x, this->_point.y, otherPoint.x, otherPoint.y, this->_color, 3);
}

void Laser::update(double diffTime)
{
    this->_point = this->_point + this->_speed * diffTime;
}

int Laser::getSize() { return 3; }

void Laser::ackHitSomething() { this->hitUntilDestroyed -= 1; }

bool Laser::wasDestroyed() { return this->hitUntilDestroyed == 0; }

int Laser::getDamage() { return 1; }

__END_API