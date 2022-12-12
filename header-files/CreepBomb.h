#ifndef CreepBomb_H
#define CreepBomb_H

#include <memory>
#include "thread.h"
#include "traits.h"

#include "Sprite.h"
#include "Enemy.h"
#include "Timer.h"
#include "configs.h"
#include "CreepBombLauncher.h"

__BEGIN_API
class CreepBombLauncher;

class CreepBomb : public Enemy
{
public:
    CreepBomb(Point point, Vector vector, std::shared_ptr<Sprite> CreepBombSprite, std::shared_ptr<Sprite> deathSprite, CreepBombLauncher * launcher);
    ~CreepBomb();

    bool getFire();
    void draw();
    void attack();
    void update(double dt);
    bool isOutOfBounds();
    void hit(int damage);
    ALLEGRO_COLOR getColor() { return this->color; }
    int getSize();

private:
    // Logic
    std::shared_ptr<Timer> explodeTimer;
    static int _CREEP_BOMB_EXPLOSION_DELAY;
    static int _CREEP_BOMB_LIFE;
    bool wasExploded;

    CreepBombLauncher * _launcher;

    // Sprites
    std::shared_ptr<Sprite> _CreepBombSprite;
    std::shared_ptr<Sprite> _deathSprite;
    ALLEGRO_COLOR color;
    int deathSpriteTimer;
    int row;
    int col;
};

__END_API

#endif