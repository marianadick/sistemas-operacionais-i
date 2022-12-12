#include "header-files/CreepBomb.h"

__BEGIN_API

int CreepBomb::_CREEP_BOMB_EXPLOSION_DELAY = Configs::_fps * 5;
int CreepBomb::_CREEP_BOMB_LIFE = 5;

CreepBomb::CreepBomb(Point point, Vector vector, std::shared_ptr<Sprite> CreepBombSprite, std::shared_ptr<Sprite> deathSprite, CreepBombLauncher * launcher) : Enemy(point, vector, CreepBomb::_CREEP_BOMB_LIFE)
{
    this->_CreepBombSprite = CreepBombSprite;
    this->_deathSprite = deathSprite;
    this->_launcher = launcher;
    this->color = al_map_rgb(150, 0, 150);
    this->deathSpriteTimer = 5;
    this->wasExploded = false;

    this->row = 0;
    this->col = 0;

    this->explodeTimer = std::make_shared<Timer>(Configs::_fps);
    this->explodeTimer->create();
    this->explodeTimer->startTimer();
}

void CreepBomb::hit(int damage)
{
    this->_life -= damage;
    if (this->col < 2)
        this->col++;
}

CreepBomb::~CreepBomb()
{
    if (this->_launcher != nullptr && Configs::_isGameRunning)
        this->_launcher->removeCreepBomb(this);
    
    this->explodeTimer.reset();
    this->_CreepBombSprite.reset();
    this->_deathSprite.reset();
}

void CreepBomb::draw()
{
    if (this->_life <= 0)
    {
        this->deathSpriteTimer -= 1;
        this->_deathSprite->draw_death_anim(this->deathSpriteTimer, this->_point, 0);
        if (this->deathSpriteTimer <= 0)
            _dead = true;
    }
    else
    {
        this->_CreepBombSprite->draw_region(this->row, this->col, 40, 41, this->_point, 0);
    }
}

bool CreepBomb::getFire()
{
    return this->explodeTimer->getCount() > CreepBomb::_CREEP_BOMB_EXPLOSION_DELAY;
}

void CreepBomb::attack()
{
    this->wasExploded = true;
}

void CreepBomb::update(double dt)
{
    if (_dead)
    {
        return;
    }

    this->_point = this->_point + this->_speed * dt;

    if (this->_point.x < 670 && this->row == 0)
        this->row++;

    if (this->_point.x < 540 && this->row == 1)
        this->row++;
}

int CreepBomb::getSize() {
    return 20; 
}

bool CreepBomb::isOutOfBounds() {
    return this->wasExploded; 
}

__END_API