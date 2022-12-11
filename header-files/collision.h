#ifndef collision_h
#define collision_h

#include "thread.h"
#include "traits.h"

#include <list>

#include "configs.h"
#include "ship.h"
#include "Projectile.h"
#include "Enemy.h"
#include "window.h"
#include "hittable.h"

__BEGIN_API
class Window;
class Ship;

class Collision {
    public:
        Collision() {};
        ~Collision() {};

        void newPlayerShot(Projectile * shot);
        void newEnemyShot(Projectile * shot);
        void newEnemyShip(Enemy * enemy);
        void removeEnemyShip(Enemy * enemy);

        /* Loop */
        void runCollision();

        /* Set windows and ship references */
        void attachShip(Ship * ship);
        void attachWindow(Window * window);
    protected:
    private:
        Ship * _ship;
        Window * _window;

        std::list<Projectile *> _shipShots;
        std::list<Projectile *> _enemiesShots;
        std::list<Enemy *> _enemies;

        void checkCollision();
        bool checkHit(Projectile * proj, Hittable * hitObj);
        bool checkHit(Drawable * firstObj, Drawable * secondObj);

        void removeObjects();
};


__END_API

#endif