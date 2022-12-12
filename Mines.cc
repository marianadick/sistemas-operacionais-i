#include "header-files/Mines.h"

__BEGIN_API

int Mine::_MINE_EXPLOSION_DELAY = Configs::_fps * 5;
int Mine::_MINE_LIFE = 3;

Mine::Mine(Point p, Vector v, std::shared_ptr<Sprite> sprite, MinesLauncher *launcher) : Enemy(p, v, Mine::_MINE_LIFE)
{
    _sprite = sprite;
    _launcher = launcher;
    _color = al_map_rgb(150, 0, 150);
    _wasExploded = false;

    _row = 0;
    _col = 0;

    _explodeTimer = std::make_shared<Timer>(Configs::_fps);
    _explodeTimer->create();
    _explodeTimer->startTimer();
}

void Mine::hit(int damage)
{
    _life -= damage;
    if (_col < 2)
        _col++;
}

Mine::~Mine()
{
    if (_launcher != nullptr && Configs::_isGameRunning == false)
        _launcher->removeMine(this);
    
    _explodeTimer.reset();
    _sprite.reset();
}

void Mine::draw()
{
    if (_life <= 0)
        _dead = true;
    else
        _sprite->draw_region(_row, _col, 40, 41, Enemy::_point, 0);
}

bool Mine::canFire()
{
    if (_explodeTimer->getCount() > Mine::_MINE_EXPLOSION_DELAY)
        return true;
    else
        return false;
}

void Mine::attack()
{
    _wasExploded = true;
}

void Mine::update(double diffTime)
{
    if (_dead)
        return;

    Enemy::_point = Enemy::_point + Enemy::_speed * diffTime;

    if (Enemy::_point.x < 670 && _row == 0)
        _row++;
    if (Enemy::_point.x < 540 && _row == 1)
        _row++;
}

int Mine::getSize() { 
    return 20; 
}

bool Mine::isOutside() {
    return _wasExploded; 
}

__END_API