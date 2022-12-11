#ifndef ENEMY_GROUP_PURPLE_H
#define ENEMY_GROUP_PURPLE_H

#include <list>
#include <memory>
#include "thread.h"
#include "traits.h"

#include "Sprite.h"
#include "window.h"
#include "collision.h"
#include "configs.h"
#include "enemyPurple.h"

__BEGIN_API

//class EnemyPurple;

class EnemyGroupPurple
{
public:
    EnemyGroupPurple();
    ~EnemyGroupPurple();
    void setWindowReference(Window * window);
    void setCollisionReference(Collision * collision);
    void removeShip(EnemyPurple * enemy);

    void run();

private:
    void loadSprites();
    void createShips();
    void processLoop();
    void handleShips();
    int DELAY_SHIPS_SPAWN;

    // Referências de Window e Collision para passar para as Ships
    Window *_window;
    Collision *_collision;

    // Sprites
    std::list<EnemyPurple *> ships;
    std::shared_ptr<Timer> shipsSpawnTimer;
    std::shared_ptr<Sprite> purpleShipSprite;
    std::shared_ptr<Sprite> enemyExplosionSprite;
};

__END_API

#endif