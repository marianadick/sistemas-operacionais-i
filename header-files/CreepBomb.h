#ifndef CreepBomb_H
#define CreepBomb_H

#include <memory>
#include "thread.h"
#include "traits.h"

#include "CreepBombLauncher.h"
#include "Sprite.h"
#include "Enemy.h"
#include "Timer.h"
#include "configs.h"

__BEGIN_API
class CreepBombLauncher;

class CreepBomb : public Enemy
{
public:
    CreepBomb(Point point, Vector vector, std::shared_ptr<Sprite> creepBombSprite, std::shared_ptr<Sprite> deathSprite, CreepBombLauncher * launcher);
    ~CreepBomb();

    void draw();
    void attack();
    void hit(int damage);
    void update(double dt);

    /* Getters */
    ALLEGRO_COLOR getColor(); // get color from Enemy
    bool getFire();
    int getSize();
    bool isOutOfBounds();

private:
    std::shared_ptr<Timer> _explodeTimer;
    static int _CREEP_BOMB_EXPLOSION_DELAY;
    static int _CREEP_BOMB_LIFE;
    bool _destroyed;

    /* It's launcher */
    CreepBombLauncher * _launcher;

    /* Sprite related */
    std::shared_ptr<Sprite> _creepBombSprite;
    std::shared_ptr<Sprite> _deathSprite;
    ALLEGRO_COLOR color;
    int _deathSpriteTimer;

    /* It's row and collumn*/
    int _row;
    int _col;
};

__END_API

#endif