#ifndef enemyPurple_h
#define enemyPurple_h

#include "threads.h"
#include "traits.h"

#include <memory>
#include "Sprite.h"
#include "enemy.h"
#include "Timer.h"
#include "configs.h"
#include "enemyPurpleControl.h"

__BEGIN_API

class EnemyPurple {
    public:
        PurpleEnemy(Point point, Vector vector, std::shared_ptr<Sprite> shipSprite, std::shared_ptr<Sprite> deathSprite, PurpleEnemiesControl *control);
        PurpleEnemy();
    protected:
    private:
}


__END_API

#endif