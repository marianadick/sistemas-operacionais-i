#ifndef HITTABLE_H
#define HITTABLE_H

#include "traits.h"
#include "Drawable.h"

__BEGIN_API

class Hittable : public Drawable
{
public:
    virtual ~Hittable() {}

    virtual void hit(int damage) = 0;
    virtual bool isDead() = 0;
    // Drawable
    virtual void draw() = 0;
    virtual void update(double diffTime) = 0;
    virtual bool isOutside() = 0;
    virtual int getSize() = 0;
    virtual Point getPosition() = 0;
};

__END_API

#endif