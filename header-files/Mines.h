#ifndef MINE_H
#define MINE_H

#include <memory>
#include "thread.h"
#include "traits.h"

#include "Sprite.h"
#include "Enemy.h"
#include "Timer.h"
#include "configs.h"
#include "MinesLauncher.h"

__BEGIN_API
class MinesLauncher;

class Mine : public Enemy
{
public:
    Mine(Point p, Vector v, std::shared_ptr<Sprite> sprite, MinesLauncher *launcher);
    ~Mine();

    bool canFire();
    void draw();
    void attack();
    void update(double dt);
    bool isOutside();
    void hit(int damage);
    ALLEGRO_COLOR getColor() { return _color; }
    int getSize();

    bool isOutOfBounds() {return false;}
    bool getFire() {return false;}

private:
    std::shared_ptr<Timer> _explodeTimer;
    static int _MINE_EXPLOSION_DELAY;
    static int _MINE_LIFE;
    bool _wasExploded;

    std::shared_ptr<Sprite> _sprite;
    ALLEGRO_COLOR _color;
    int _row;
    int _col;

    MinesLauncher *_launcher;
};

__END_API

#endif