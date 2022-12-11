#include "header-files/collision.h"
#include <allegro5/allegro_primitives.h>

__BEGIN_API

void Collision::runCollision()
{
    while (Configs::_isGameRunning)
    {
        checkCollision();
        removeObjects();
        Thread::yield();
    }
}

void Collision::checkCollision()
{
    // Ship x Enemy
    for (auto listItem = _shipShots.begin(); listItem != _shipShots.end();)
    {
        Projectile * shipShots = *listItem; listItem++;

        // Checks if an enemy was hit
        for (auto enemyItem = _enemies.begin(); enemyItem != _enemies.end();)
        {
            Enemy * enemy = *enemyItem; enemyItem++;

            if (checkHit(shipShots, enemy))
            {
                enemy->hit(shipShots->getDamage());
                if (enemy->isDead())
                {
                    _window->removeDrawableItem(enemy);
                    _enemies.remove(enemy);
                    delete enemy;
                }

                // Checks if ship shot hit something
                shipShots->ackHitSomething();

                // Checks if the shot was destroyed, if so remove it from window
                if (shipShots->wasDestroyed())
                {
                    _window->removeDrawableItem(shipShots);
                    shipShots.remove(shipShots);
                    delete shipShots;
                    break;
                }
            }
        }
    }

    // Enemy x Ship 
    for (auto listItem = _enemiesShots.begin(); listItem != _enemiesShots.end();)
    {
        Projectile *enemyShot = *listItem; listItem++;

        if (checkHit(enemyShot, _ship))
        {
            // Checks if an enemy hit something
            enemyShot->ackHitSomething();

            // Inflicts the damage to the player
            _ship->hit(enemyShot->getDamage());

            // Checks if the shot was destroyed, if so remove it from window
            if (enemyShot->wasDestroyed())
            {
                // Destrói o tiro
                _window->removeDrawableItem(enemyShot);
                _enemiesShots.remove(enemyShot);
                delete enemyShot;
            }

            if (_ship->isDead())
            {
                GameConfigs::finished = true;
                return;
            }
        }
    }

    // Checks if the enemy ship and the player ship collided
    for (auto listItem = _enemies.begin(); listItem != _enemies.end();)
    {
        Enemy *enemy = *listItem; listItem++;

        if (checkHit(enemy, _ship))
        {
            enemy->hit(1);

            if (enemy->isDead())
            {
                _window->removeDrawableItem(enemy);
                _enemies.remove(enemy);
                delete enemy;
            }

            _ship->hit(1);
            if (_ship->isDead())
            {
                Configs::_isGameRunning = true;
                return;
            }
        }
    }
}

bool Collision::checkHit(Projectile * proj, Hittable * hitObj)
{
    Point projPos = proj->getPosition();
    Point hitPos = hitObj->getPosition();
    int hitSize = hitObj->getSize();

    if (projPos.x > hitPos.x - hitSize &&
        (projPos.x < hitPos.x + hitSize) &&
        (projPos.y > hitPos.y - hitSize) &&
        (projPos.y < hitPos.y + hitSize))
        return true;
    return false;
}

bool Collision::checkHit(Drawable * firstObj, Drawable * secondObj)
{
    int firstSize = firstObj->getSize();
    int secondSize = secondObj->getSize();
    Point firstPos = firstObj->getPosition();
    Point secondPos = secondObj->getPosition();

    return (abs(firstPos.x - secondPos.x) < (firstSize + secondSize) && 
            abs(firstPos.y - secondPos.y) < (firstSize + secondSize));
}

void Collision::removeObjects()
{
    // Remove enemies
    for (auto enemyItem = _enemies.begin(); enemyItem != _enemies.end();)
    {
        Enemy * enemy = *enemyItem; enemyItem++;
        if (enemy->isOutside())
        {
            _window->removeDrawableItem(enemy);
            _enemies.remove(enemy);
            delete enemy;
        }
    }

    // Remove enemies shots
    for (auto enemyItem = _enemiesShots.begin(); enemyItem != _enemiesShots.end();)
    {
        Projectile * projectile = *enemyItem; enemyItem++;
        if (projectile->isOutside())
        {
            _window->removeDrawableItem(projectile);
            _enemiesShots.remove(projectile);
            delete projectile;
        }
    }

    // Remove player shots
    for (auto shipShots = shipShots.begin(); shipShots != shipShots.end();)
    {
        Projectile * projectile = *shipShots; shipShots++;
        if (projectile->isOutside())
        {
            _window->removeDrawableItem(projectile);
            shipShots.remove(projectile);
            delete projectile;
        }
    }
}

void Collision::attachShip(PlayerShip * ship) {
     _ship = ship; 
}

void Collision::attachWindow(Window * window) {
     _window = window; 
}

void Collision::newPlayerShot(Projectile * proj) { 
    playerShots.push_front(proj); 
}

void Collision::newEnemyShot(Projectile * proj) {
     enemiesShots.push_front(proj); 
}

void Collision::newEnemyShip(Enemy * enemy) {
     enemies.push_front(enemy); 
}

void Collision::removeEnemyShip(Enemy * enemy) {
     enemies.remove(enemy); 
}


__END_API