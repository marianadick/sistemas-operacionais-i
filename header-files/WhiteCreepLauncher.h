#ifndef whiteCreepLauncher_h
#define whiteCreepLauncher_h

#include <list>
#include <memory>
#include "thread.h"
#include "traits.h"

#include "Sprite.h"
#include "window.h"
#include "CollisionHandler.h"
#include "configs.h"
#include "Creep.h"

__BEGIN_API

class Creep;

class WhiteCreepLauncher : public Launcher
{
public:
    WhiteCreepLauncher();
    ~WhiteCreepLauncher();

    void attachWindow(Window * window);
    void attachCollision(CollisionHandler * collisionHandler);
    void removeCreep(Creep * creep);

    void runLauncher();

private:
    int NEW_GROUP_DELAY;

    void loadSprites();
    void createCreepGroup();
    void createCreepBehavior();
    void updateAngle(Creep * creep);
    void updateVector(Creep * creep);

    /* Reference to game state and obj*/
    Window *_window;
    CollisionHandler *_collisionHandler;

    std::list<Creep *> creeps;

    std::shared_ptr<Timer> newGroupTimer;
    std::shared_ptr<Sprite> purpleCreepSprite;
};

__END_API

#endif