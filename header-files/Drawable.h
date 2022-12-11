#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "traits.h"
#include "Point.h"

__BEGIN_API

class Drawable
{
public:
    virtual ~Drawable() {}

    virtual void hit(int damage) = 0;
    virtual bool isDead() = 0;

    virtual void draw() = 0;
    virtual void update(double diffTime) = 0;
    virtual bool isOutOfBounds() = 0;
    virtual int getSize() = 0;
    virtual Point getPosition() = 0;
};

__END_API

#endif