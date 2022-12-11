#ifndef enemyPurple_h
#define enemyPurple_h

#include "threads.h"
#include "traits.h"

#include <memory>
#include "Sprite.h"
#include "Enemy.h"
#include "Timer.h"
#include "configs.h"

#include "enemyGroupPurple.h"

__BEGIN_API

class EnemyPurple : public Enemy {
    public:
        EnemyPurple(Point point, Vector vector, std::shared_ptr<Sprite> shipSprite, std::shared_ptr<Sprite> deathSprite, EnemyGroupPurple *enemyGroup);
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

        /* Shot delay */
        static int _SHOTS_DELAY;
        std::shared_ptr<Timer> _shotsTimer;

        /* Reference to its controller */
        EnemyGroupPurple * _enemyGroup;

        /* Enemy sprites */
        std::shared_ptr<Sprite> _shipSprite;
        std::shared_ptr<Sprite> _deathSprite;

        Point _point;
        Vector _vector;

        /* Color and timer of sprite */
        ALLEGRO_COLOR _color;
        int _deathSpriteTimer;
};

__END_API

#endif