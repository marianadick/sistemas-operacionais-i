#ifndef Mines_Launcher_h
#define Mines_Launcher_h

#include <list>
#include <memory>
#include "thread.h"
#include "traits.h"

#include "Sprite.h"
#include "window.h"
#include "CollisionHandler.h"
#include "configs.h"
#include "Mines.h"

__BEGIN_API
class Mine;
class Window;
class CollisionHandler;

class MinesLauncher
{
public:
    MinesLauncher();
    ~MinesLauncher();
    void setWindowReference(Window *window);
    void setCollisionReference(CollisionHandler *collision);
    void removeMine(Mine *enemy);

    void runMineLauncher();

private:
    void loadSprites();
    void createMine();
    void processLoop();
    void handleMines();

    Window *_window;
    CollisionHandler *_collision;

    static int _DELAY_MINE_SPAWN;

    std::list<Mine *> _mines;
    std::shared_ptr<Timer> _minesSpawnTimer;
    std::shared_ptr<Sprite> _mineSprite;
    std::shared_ptr<Sprite> _mineExplosionSprite;
    ALLEGRO_COLOR _color;
};

__END_API

#endif