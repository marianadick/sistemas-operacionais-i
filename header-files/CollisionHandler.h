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
#include <allegro5/allegro_primitives.h>
#include "Mines.h"

__BEGIN_API
class Window;
class Ship;
class Mine;

class CollisionHandler {
    public:
        CollisionHandler() {};
        ~CollisionHandler() {};

        void newPlayerShot(Projectile * shot);
        void newEnemyShot(Projectile * shot);
        void newEnemyShip(Enemy * enemy);
        void removeEnemyShip(Enemy * enemy);

        void newMine(Mine * mine);
        void removeMine(Mine * mine);

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
        std::list<Mine *> _mines;

        void checkCollision();
        void checkCollisionOnEnemies();
        void checkCollidingEnemyWithPlayer();
        void checkCollisionOnPlayer();

        bool checkHit(Projectile * proj, Enemy * target); // Checks Player shot -> Enemy Ship
        void checkHit(Projectile * proj, Ship * target); // Checks Enemy shot -> Player Ship
        void checkHit(Drawable * firstObj, Drawable * secondObj); // Checks if Player ship is colliding with the Enemy Ship

        void clearEnemies();
        void clearProjectiles();
        void clearMines();
};

__END_API

#endif