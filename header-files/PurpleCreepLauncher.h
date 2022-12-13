#ifndef purpleCreepLauncher_h
#define purpleCreepLauncher_h

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
    ~PurpleCreepLauncher() {};

    void runLauncher();
    void removeCreep(Creep * creep);

    /* Set references to the window and collisionHandler */
    void attachWindow(Window * window);
    void attachCollision(CollisionHandler * collisionHandler);
private:
    static int _NEW_GROUP_DELAY;

    void loadSprites();
    void createCreepGroup();
    void createCreepBehavior();

    /* Reference to thee window and collisionHandler */
    Window *_window;
    CollisionHandler *_collisionHandler;

    /* Stores the purple creeps */
    std::list<Creep *> _creeps;

    std::shared_ptr<Timer> _newGroupTimer;
    std::shared_ptr<Sprite> _purpleCreepSprite;
};

__END_API

#endif