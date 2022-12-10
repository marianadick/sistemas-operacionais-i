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
    Laser(Point point, ALLEGRO_COLOR color, Vector vector, bool isPlayerShot);
    ~Laser();

    int getDamage();
    void ackHitSomething();
    bool wasDestroyed();

    void draw();
    void update(double diffTime);
    int getSize();

private:
    int hitUntilDestroyed;
};

__END_API

#endif