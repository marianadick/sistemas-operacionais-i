#ifndef MINES_CONTROL_H
#define MINES_CONTROL_H

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
class Mine; // Forward declaration, avoid compilation error
class Window;
class CollisionHandler;

class MinesControl
{
public:
    MinesControl();
    ~MinesControl();
    void setWindowReference(Window *window);
    void setCollisionHandlerReference(CollisionHandler *CollisionHandler);
    void removeMine(Mine *enemy);

    void run();

private:
    void loadSprites();
    void createMine();
    void processLoop();
    void handleMines();

    // Referências de Window e CollisionHandler para passar para as Ships
    Window *_window;
    CollisionHandler *_CollisionHandler;

    static int DELAY_MINE_SPAWN;

    // Sprites
    std::list<Mine *> mines;
    std::shared_ptr<Timer> minesSpawnTimer;
    std::shared_ptr<Sprite> mineSprite;
    std::shared_ptr<Sprite> mineExplosionSprite;
    ALLEGRO_COLOR _color;
};

__END_API

#endif