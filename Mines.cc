#include "header-files/Mines.h"

__BEGIN_API
// 5 seg
int Mine::MINE_EXPLOSION_DELAY = Configs::_fps * 5;
int Mine::MINE_LIFE = 5;

Mine::Mine(Point point, Vector vector, std::shared_ptr<Sprite> mineSprite, std::shared_ptr<Sprite> deathSprite, MinesControl *control) : Enemy(point, vector, Mine::MINE_LIFE)
{
    this->_mineSprite = mineSprite;
    this->_deathSprite = deathSprite;
    this->_control = control;
    this->color = al_map_rgb(150, 0, 150);
    this->deathSpriteTimer = 5;
    this->wasExploded = false;

    this->row = 0;
    this->col = 0;

    this->explodeTimer = std::make_shared<Timer>(Configs::_fps);
    this->explodeTimer->create();
    this->explodeTimer->startTimer();
}

void Mine::hit(int damage)
{
    this->_life -= damage;
    if (this->col < 2)
        this->col++;
}

Mine::~Mine()
{
    if (this->_control != nullptr && Configs::_isGameRunning)
        this->_control->removeMine(this);
    
    this->explodeTimer.reset();
    this->_mineSprite.reset();
    this->_deathSprite.reset();
}

void Mine::draw()
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
        this->_mineSprite->draw_region(this->row, this->col, 40, 41, this->_point, 0);
    }
}

bool Mine::getFire()
{
    return this->explodeTimer->getCount() > Mine::MINE_EXPLOSION_DELAY;
}

void Mine::attack()
{
    this->wasExploded = true;
}

void Mine::update(double diffTime)
{
    if (_dead)
    {
        return;
    }

    this->_point = this->_point + this->_speed * diffTime;

    if (this->_point.x < 670 && this->row == 0)
        this->row++;

    if (this->_point.x < 540 && this->row == 1)
        this->row++;
}

int Mine::getSize() { return 20; }

bool Mine::isOutOfBounds() { return this->wasExploded; }

__END_API