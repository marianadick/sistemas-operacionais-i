#include "header-files/enemyPurple.h"

__BEGIN_API

int EnemyPurple::_SHOTS_DELAY = 50;

EnemyPurple::EnemyPurple(Point point, Vector vector, std::shared_ptr<Sprite> shipSprite, 
                        std::shared_ptr<Sprite> deathSprite, EnemyGroupPurple * enemyGroup) {
    _point = point;
    _vector = vector;
    
    _shipSprite = shipSprite;
    _deathSprite = deathSprite;

    _enemyGroup = enemyGroup;

    _color = al_map_rgb(150, 0, 150);
    _deathSpriteTimer = 5;

    _shotsTimer = std::make_shared<Timer>(Configs::_fps);
    _shotsTimer->create();
    _shotsTimer->startTimer();
}

EnemyPurple::~EnemyPurple() {
    if (_enemyGroup != nullptr)
        _enemyGroup->removeShip(this);
}

void EnemyPurple::draw()
{
    if (isDead())
    {
        _deathSpriteTimer -= 1;
        _deathSprite->draw_death_anim(_deathSpriteTimer, _point, 0);
    }
    else
    {
        _shipSprite->draw_tinted(_point, _color, 0);
    }
}

void EnemyPurple::update(double dt)
{
    _point = _point + _speed * dt;
    if (_shotsTimer->getCount() > EnemyPurple::_SHOTS_DELAY + rand() % 60)
    {
        _canFire = true;
        _shotsTimer->srsTimer();
    }
}

void EnemyPurple::attack() { 
    _canFire = false; 
}

ALLEGRO_COLOR EnemyPurple::getColor() { 
    return _color; 
}

int EnemyPurple::getSize() { 
    return 20; 
}

bool EnemyPurple::canFire() { 
    return _canFire; 
}

bool EnemyPurple::isOutside() { 
    return _point.x < -40; 
}

__END_API