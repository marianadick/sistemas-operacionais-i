#include <allegro5/allegro_primitives.h>
#include "header-files/Laser.h"

__BEGIN_API

Laser::Laser(Point point, ALLEGRO_COLOR color, Vector speed) : Projectile(point, color, speed)
{
    this->isActive = true;
}


void Laser::draw()
{
    Point otherPoint = this->_point + this->_speed * (0.05);
    al_draw_line(this->_point.x, this->_point.y, otherPoint.x, otherPoint.y, this->_color, 3);
}

void Laser::update(double diffTime)
{
    this->_point = this->_point + this->_speed * diffTime;
    this->isActive = this->stillLive();
}

int Laser::getSize() { return 3; }

Point Laser::getPosition() { return this->_point; }

bool Laser::stillLive()
{
    if ((this->_point.x > Configs::_widthDisplay) ||
        (this->_point.x < 0) ||
        (this->_point.y > Configs::_heightDisplay) ||
        (this->_point.y < 0))
        return false;
    return true;
}

__END_API
