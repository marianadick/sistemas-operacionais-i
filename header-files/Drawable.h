#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "traits.h"
#include "Point.h"

__BEGIN_API

class Drawable
{
public:
    virtual ~Drawable() {}

    virtual void draw() = 0;
    virtual void update(double diffTime) = 0;
};

__END_API

#endif