#ifndef enemy_h
#define ENEMY_H

#include "hittable.h"
#include "traits.h"
#include "Drawable.h"
#include "Point.h"
#include "Vector.h"

__BEGIN_API

class Enemy : public Hittable {
    public:
        Enemy(Point point, Vector vector, int nLife) {
            _life = nLife;
            _point = point;
            _speed = vector;
        }

        virtual void draw() = 0;
        virtual void update(double dt) = 0;
        virtual bool isOutside() = 0;
        virtual int getSize() = 0;
        virtual bool canFire() = 0;

        bool isDead() { return _life <= 0; }
        Point getPosition() { return _point; }
        Vector getVector() { return _speed; }
        void hit(int damage) { _life -= damage; }
        int getLife() { return _life; }

    protected:
        int _life;
        Point _point;
        Vector _speed;
};

__END_API

#endif