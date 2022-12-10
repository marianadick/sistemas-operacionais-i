#include "traits.h"
#include "Drawable.h"
#include "Point.h"
#include "Vector.h"

#include <allegro5/allegro.h>

__BEGIN_API

class Projectile : public Drawable
{
public:
    Projectile(Point point, ALLEGRO_COLOR color, Vector speed) : _point(point), _color(color), _speed(speed), isActive(true) {}

    virtual void draw() = 0;
    virtual void update(double diffTime) = 0;
    virtual bool stillLive() = 0;
    virtual int getSize() = 0;
    virtual Point getPosition() = 0;

protected:
    Point _point;
    ALLEGRO_COLOR _color;
    Vector _speed;
    bool isActive;
};

__END_API