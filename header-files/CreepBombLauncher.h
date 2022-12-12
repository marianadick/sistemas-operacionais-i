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

    void runCreepBombLauncher();

    void setWindowReference(Window *window);
    void setCollisionHandlerReference(CollisionHandler *CollisionHandler);
    void removeCreepBomb(CreepBomb *enemy);

protected:
private:
    void processLoop(); // Loop waiting for its timer (delay)
    void handleCreepBombs();
    void createCreepBomb();
    void loadSprites();

    /* Sprites*/
    std::shared_ptr<Sprite> _creepBombsSprite;
    std::shared_ptr<Sprite> _creepBombsExplosionSprite;

    /* Reference to the window and collisionHandler */
    Window *_window;
    CollisionHandler *_collisionHandler;

    std::list<CreepBomb *> _creepBombs;

    /* Timer */
    std::shared_ptr<Timer> _creepBombsSpawnTimer;
    static int _DELAY_BOMBS_SPAWN;

    ALLEGRO_COLOR _color;
};

__END_API

#endif