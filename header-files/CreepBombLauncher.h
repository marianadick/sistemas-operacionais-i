#ifndef Creep_Bomb_Launcher_h
#define Creep_Bomb_Launcher_h

#include <list>
#include <memory>
#include "thread.h"
#include "traits.h"

#include "Sprite.h"
#include "window.h"
#include "CollisionHandler.h"
#include "configs.h"
#include "CreepBomb.h"

__BEGIN_API
class CreepBomb;
class Window;
class CollisionHandler;

class CreepBombLauncher
{
public:
    CreepBombLauncher();
    ~CreepBombLauncher();
    void setWindowReference(Window *window);
    void setCollisionHandlerReference(CollisionHandler *CollisionHandler);
    void removeCreepBomb(CreepBomb *enemy);

    void runCreepBombLauncher();

private:
    void loadSprites();
    void createCreepBomb();
    void processLoop();
    void handleCreepBombs();

    Window *_window;
    CollisionHandler *_CollisionHandler;

    static int _DELAY_BOMBS_SPAWN;

    std::list<CreepBomb *> _creepBombs;
    std::shared_ptr<Timer> _creepBombsSpawnTimer;
    std::shared_ptr<Sprite> _creepBombsSprite;
    std::shared_ptr<Sprite> _creepBombsExplosionSprite;
    ALLEGRO_COLOR _color;
};

__END_API

#endif