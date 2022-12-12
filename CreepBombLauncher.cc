#include "header-files/CreepBombLauncher.h"

__BEGIN_API

int CreepBombLauncher::_DELAY_BOMBS_SPAWN = Configs::_fps * 3;

CreepBombLauncher::CreepBombLauncher()
{
    this->loadSprites();
    this->_color = al_map_rgb(255, 0, 0);
    this->_creepBombsSpawnTimer = std::make_shared<Timer>(Configs::_fps);
    this->_creepBombsSpawnTimer->create();
    this->_creepBombsSpawnTimer->startTimer();
}

CreepBombLauncher::~CreepBombLauncher()
{
    this->_creepBombsSpawnTimer.reset();
    this->_creepBombsSprite.reset();
    this->_creepBombsExplosionSprite.reset();
}

void CreepBombLauncher::setWindowReference(Window *window) { 
    this->_window = window; 
}
void CreepBombLauncher::setCollisionHandlerReference(CollisionHandler *collision) {
    this->_CollisionHandler = collision; 
}
void CreepBombLauncher::removeCreepBomb(CreepBomb *enemy)
{
    if (this->_creepBombs.size() == 0)
        return;

    if (Configs::_isGameRunning)
        this->_creepBombs.remove(enemy);
    else
        this->_creepBombs.clear();
}

void CreepBombLauncher::runCreepBombLauncher()
{
    this->loadSprites();
    while (Configs::_isGameRunning)
    {
        if (this->_window == nullptr || this->_CollisionHandler == nullptr)
        {
            Thread::yield();
            continue;
        }

        this->processLoop();
        Thread::yield();
    }
}

void CreepBombLauncher::processLoop()
{
    if (this->_creepBombsSpawnTimer->getCount() > this->_DELAY_BOMBS_SPAWN)
        this->createCreepBomb();
    this->handleCreepBombs();
}

void CreepBombLauncher::handleCreepBombs()
{
    for (auto creepBombItem = this->_creepBombs.begin(); creepBombItem != this->_creepBombs.end();)
    {
        CreepBomb *creepBomb = *creepBombItem;
        creepBombItem++;

        // Caso a mina já tenha sido destruída mas não foi removida ainda
        if (creepBomb->getDead() || creepBomb->isOutOfBounds())
            continue;

        // Caso a mina já esteja pronta para atacar
        if (creepBomb->getFire())
        {
            // Executa o ataque
            creepBomb->attack();
            for (int i = -500; i <= 500; i += 325)
            {
                for (int j = -500; j <= 500; j += 325)
                {
                    // Cria o tiro a adiciona nas listas
                    Laser *laser = new Laser(creepBomb->getPosition(), this->_color, Vector(i, j), false);
                    this->_CollisionHandler->newEnemyShot(laser);
                    this->_window->addProjectile(laser);
                }
            }
        }
    }
}

void CreepBombLauncher::createCreepBomb()
{
    // Gera um ponto aleatório em y para a bomba aparecer
    Point point = Point(0, 0);
    point.rollRandom();
    point.x = Configs::_widthDisplay;

    // Cria uma mina
    CreepBomb *creepBomb = new CreepBomb(point, Vector(-100, 0), this->_creepBombsSprite, this->_creepBombsExplosionSprite, this);

    // Adiciona referência dela nas listas
    this->_creepBombs.push_back(creepBomb);
    this->_CollisionHandler->newEnemyShip(creepBomb);
    this->_window->addEnemy(creepBomb);

    // Reset o timer
    this->_creepBombsSpawnTimer->srsTimer();
}

void CreepBombLauncher::loadSprites()
{
    // Go to resources directory
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));

    this->_creepBombsSprite = std::make_shared<Sprite>("spikebomb.png");
    this->_creepBombsExplosionSprite = std::make_shared<Sprite>("explode.png");
    al_destroy_path(path);
}

__END_API