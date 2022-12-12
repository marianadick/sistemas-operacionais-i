#ifndef ENEMY_H
#define ENEMY_H

#include "traits.h"
#include "Drawable.h"
#include "Point.h"
#include "Vector.h"

__BEGIN_API

class Enemy : public Drawable
{
public:
    Enemy(Point point, Vector vector, int life)
    {
        _dead = false;
        _life = life;
        _point = point;
        _speed = vector;
    }

    virtual void draw() = 0;
    virtual void update(double diffTime) = 0;
    virtual bool isOutOfBounds() = 0;
    virtual int getSize() = 0;
    virtual bool getFire() = 0;

    Point getPosition() { return _point; }
    Vector getVector() { return _speed; }
    void hit(int damage) { _life -= damage; }
    bool getDead() { return _life <= 0 && _dead; }
    int getLife() { return _life; }

protected:
    Point _point;
    Vector _speed;
    bool _dead;
    int _life;
};

__END_API

#endif