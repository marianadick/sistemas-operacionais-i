#include "header-files/CreepBomb.h"

__BEGIN_API

int CreepBomb::_CREEP_BOMB_EXPLOSION_DELAY = Configs::_fps * 7;
int CreepBomb::_CREEP_BOMB_LIFE = 5;

CreepBomb::CreepBomb(Point point, Vector vector, std::shared_ptr<Sprite> creepBombSprite, std::shared_ptr<Sprite> deathSprite, CreepBombLauncher * launcher) : 
                        Enemy(point, vector, CreepBomb::_CREEP_BOMB_LIFE)
{
    _creepBombSprite = creepBombSprite;
    _deathSprite = deathSprite;
    _launcher = launcher;
    _col = 0; 
    _row = 0;
    _deathSpriteTimer = 5;
    _destroyed = false;
    this->color = al_map_rgb(150, 0, 150);
    _explodeTimer = std::make_shared<Timer>(Configs::_fps);
    _explodeTimer->create();
    _explodeTimer->startTimer();
}

CreepBomb::~CreepBomb()
{
    if (_launcher != nullptr && Configs::_isGameRunning)
        _launcher->removeCreepBomb(this);
    
    _deathSprite.reset();
    _creepBombSprite.reset();
    _explodeTimer.reset();
}

void CreepBomb::draw()
{
    if (_life <= 0) // if it has no more lives
    {
        _deathSpriteTimer -= 1;
        _deathSprite->draw_death_anim(_deathSpriteTimer, _point, 0);
        if (_deathSpriteTimer <= 0) // if time expired
            _dead = true;
    }
    else // if it is still alive
        _creepBombSprite->draw_region(_row, _col, 40, 41, _point, 0);
}

void CreepBomb::attack()
{
    _destroyed = true;
}

void CreepBomb::hit(int damage)
{
    _life = _life - damage;
    if (_col < 2)
        _col++;
}

void CreepBomb::update(double dt)
{
    if (_dead)
        return;
    _point = _point + _speed * dt;
    if (_point.x < 670 && _row == 0)
        _row++;
    if (_point.x < 540 && _row == 1)
        _row++;
}

ALLEGRO_COLOR CreepBomb::getColor() {
     return this->color; 
}

bool CreepBomb::getFire() {
    // Can only fire in the right time
    if ( _explodeTimer->getCount() > CreepBomb::_CREEP_BOMB_EXPLOSION_DELAY)
        return true;
    else
        return false;
}

int CreepBomb::getSize() {
    return 20; 
}

bool CreepBomb::isOutOfBounds() {
    return _destroyed; 
}

__END_API