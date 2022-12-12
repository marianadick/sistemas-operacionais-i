#include "header-files/CreepBombLauncher.h"

__BEGIN_API

int CreepBombLauncher::_DELAY_BOMBS_SPAWN = Configs::_fps * 30;

CreepBombLauncher::CreepBombLauncher()
{
    _creepBombsSpawnTimer = std::make_shared<Timer>(Configs::_fps);
    _creepBombsSpawnTimer->create();
    _creepBombsSpawnTimer->startTimer();
    _color = al_map_rgb(255, 255, 0);
    loadSprites();
}

CreepBombLauncher::~CreepBombLauncher()
{
    _creepBombsExplosionSprite.reset();
    _creepBombsSpawnTimer.reset();
    _creepBombsSprite.reset();
}

void CreepBombLauncher::removeCreepBomb(CreepBomb *enemy)
{
    // No bombs
    if (!_creepBombs.size())
        return;

    if (Configs::_isGameRunning)
        _creepBombs.remove(enemy);
    else
        _creepBombs.clear();
}

void CreepBombLauncher::runCreepBombLauncher()
{
    while (Configs::_isGameRunning)
    {
        // While undefinied references, wait
        if (_window == nullptr || _collisionHandler == nullptr)
        {
            Thread::yield();
            continue;
        }
        processLoop();
        Thread::yield();
    }
}

void CreepBombLauncher::processLoop()
{
    if (_creepBombsSpawnTimer->getCount() > _DELAY_BOMBS_SPAWN) {
        createCreepBomb();
        _creepBombsSpawnTimer->srsTimer();
    }
    handleCreepBombs();
}

void CreepBombLauncher::handleCreepBombs()
{
    for (auto creepBombItem = _creepBombs.begin(); creepBombItem != _creepBombs.end();)
    {
        CreepBomb *creepBomb = *creepBombItem;
        creepBombItem++;

        // if dead or destroyed
        if (creepBomb->getDead() || creepBomb->isOutOfBounds())
            continue;

        if (creepBomb->getFire())
        {
            creepBomb->attack();
            for (int i = -500; i <= 500; i += 325)
            {
                for (int j = -500; j <= 500; j += 325)
                {
                    // Cria o tiro a adiciona nas listas
                    Laser *laser = new Laser(creepBomb->getPosition(), _color, Vector(i, j), false);
                    _collisionHandler->newEnemyShot(laser);
                    _window->addProjectile(laser);
                }
            }
        }
    }
}

void CreepBombLauncher::createCreepBomb()
{
    Point point = Point(800, 0);
    point.rollRandomY();

    CreepBomb * creepBomb = new CreepBomb(point, Vector(-50, 0), _creepBombsSprite, _creepBombsExplosionSprite, this);

    _creepBombs.push_back(creepBomb);
    _collisionHandler->newEnemyShip(creepBomb);
    _window->addEnemy(creepBomb);
}

void CreepBombLauncher::loadSprites()
{
    // Go to resources directory
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));

    _creepBombsSprite = std::make_shared<Sprite>("spikebomb.png");
    _creepBombsExplosionSprite = std::make_shared<Sprite>("explode.png");
    al_destroy_path(path);
}

void CreepBombLauncher::setWindowReference(Window *window) { 
    _window = window; 
}

void CreepBombLauncher::setCollisionHandlerReference(CollisionHandler *collision) {
    _collisionHandler = collision; 
}

__END_API