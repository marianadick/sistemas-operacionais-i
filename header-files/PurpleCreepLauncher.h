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
#include "Creep.h"

__BEGIN_API

class Creep;

class PurpleCreepLauncher : public Launcher
{
public:
    PurpleCreepLauncher();
    ~PurpleCreepLauncher();

    void attachWindow(Window * window);
    void attachCollision(CollisionHandler * collisionHandler);
    void removeCreep(Creep * creep);

    void runLauncher();

private:
    int NEW_GROUP_DELAY;

    void loadSprites();
    void createCreepGroup();
    void createCreepBehavior();

    /* Reference to game state and obj*/
    Window *_window;
    CollisionHandler *_collisionHandler;

    std::list<Creep *> creeps;

    std::shared_ptr<Timer> newGroupTimer;
    std::shared_ptr<Sprite> purpleCreepSprite;
};

__END_API

#endif