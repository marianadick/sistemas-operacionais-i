#ifndef enemyPurple_h
#define enemyPurple_h

#include "threads.h"
#include "traits.h"

#include <memory>
#include "Sprite.h"
#include "enemy.h"
#include "Timer.h"
#include "configs.h"

__BEGIN_API

class EnemyPurple : Enemy {
    public:
        EnemyPurple(Point point, Vector vector, std::shared_ptr<Sprite> shipSprite, std::shared_ptr<Sprite> deathSprite, PurpleEnemiesControl *control);
        ~EnemyPurple();

        void draw();
        void update(double dt);
        void attack();

        /* Getters */
        ALLEGRO_COLOR getColor();
        int getSize();
        bool canFire();
        bool isOutside();
    
    protected:
    private:
        /* Checks if enemy is able to fire */
        bool _canFire;

        /* SHot delay*/
        static int _SHOTS_DELAY;
        std::shared_ptr<Timer> _shotsTimer;

        /* Reference to its controller */
        EnemyGroupPurple * _controller;

        /* Enemy sprites */
        std::shared_ptr<Sprite> _shipSprite;
        std::shared_ptr<Sprite> _deathSprite;

        Point _point;
        Vector _vector;

        /* Color and timer of sprite */
        ALLEGRO_COLOR _color;
        int _deathSpriteTimer;
}

__END_API

#endif