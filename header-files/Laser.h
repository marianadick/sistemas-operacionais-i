#ifndef LASER_H
#define LASER_H

#include <allegro5/allegro.h>

#include "traits.h"
#include "Point.h"
#include "Vector.h"
#include "Projectile.h"
#include "configs.h"

__BEGIN_API

class Laser : public Projectile
{
public:
    Laser(Point p, ALLEGRO_COLOR c, Vector s);
    ~Laser();

    void draw();
    bool stillLive();
    void update(double diffTime);
    int getSize();
    Point getPosition();
};

__END_API

#endif