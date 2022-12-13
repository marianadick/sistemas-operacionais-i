#ifndef whiteCreepLauncher_h
#define whiteCreepLauncher_h

#include <list>
#include <memory>
#include "thread.h"
#include "traits.h"
#include <cmath>

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
    ~WhiteCreepLauncher() {};

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

    void updateAngle(Creep * creep); // Update the angle to where it is shooting
    void updateVector(Creep * creep); // Update the vector to where the shot should go

    /* Reference to thee window and collisionHandler */
    Window *_window;
    CollisionHandler *_collisionHandler;

    /* Stores the white creeps */
    std::list<Creep *> _creeps;

    std::shared_ptr<Timer> _newGroupTimer;
    std::shared_ptr<Sprite> _whiteCreepSprite;
};

__END_API

#endif