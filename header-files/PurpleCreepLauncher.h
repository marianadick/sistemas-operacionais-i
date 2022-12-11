#ifndef ENEMY_GROUP_PURPLE_H
#define ENEMY_GROUP_PURPLE_H

#include <list>
#include <memory>
#include "thread.h"
#include "traits.h"

#include "Sprite.h"
#include "window.h"
#include "CollisionHandler.h"
#include "configs.h"
#include "PurpleCreep.h"

__BEGIN_API

class PurpleCreep;

class PurpleCreepLauncher
{
public:
    PurpleCreepLauncher();
    ~PurpleCreepLauncher();
    void attachWindow(Window * window);
    void attachCollision(CollisionHandler * collision);
    void removeShip(PurpleCreep * enemy);

    void run();

private:
    void loadSprites();
    void createShips();
    void processLoop();
    void handleShips();
    int DELAY_SHIPS_SPAWN;

    // Referências de Window e CollisionHandler para passar para as Ships
    Window *_window;
    CollisionHandler *_collision;

    // Sprites
    std::list<PurpleCreep *> ships;
    std::shared_ptr<Timer> shipsSpawnTimer;
    std::shared_ptr<Sprite> purpleShipSprite;
    std::shared_ptr<Sprite> enemyExplosionSprite;
};

__END_API

#endif