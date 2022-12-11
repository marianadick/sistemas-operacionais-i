#ifndef ENEMY_H
#define ENEMY_H

#include "traits.h"
#include "Drawable.h"
#include "hittable.h"
#include "Point.h"
#include "Vector.h"

__BEGIN_API

class Enemy : public Hittable
{
public:
    Enemy(Point point, Vector vector, int life)
    {
        this->life = life;
        this->_point = point;
        this->_speed = vector;
    }

    virtual void draw() = 0;
    virtual void update(double diffTime) = 0;
    virtual bool isOutside() = 0;
    virtual int getSize() = 0;
    virtual bool canFire() = 0;

    Point getPosition() { return this->_point; }
    Vector getVector() { return this->_speed; }
    void hit(int damage) { this->life -= damage; }
    bool isDead() { return this->life <= 0; }
    int getLife() { return this->life; }

protected:
    Point _point;
    Vector _speed;
    int life;
};

__END_API

#endif