#ifndef LASER_H
#define LASER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "configs.h"
#include "Projectile.h"

#include "traits.h"
#include "Point.h"
#include "Vector.h"

__BEGIN_API

class Laser : public Projectile
{
public:
    Laser(Point point, ALLEGRO_COLOR color, Vector vector, bool isPlayerShot);
    ~Laser();

    void draw();
    void update(double dt);

    /* Getters */
    int getSize();
    int getDamage();
    bool wasDestroyed();

    void ackHitSomething();
private:
    bool _destroyed;
};

__END_API

#endif