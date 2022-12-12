
#include "header-files/MinesLauncher.h"

__BEGIN_API

int MinesLauncher::_DELAY_MINE_SPAWN = Configs::_fps * 3;

MinesLauncher::MinesLauncher()
{
    loadSprites();
    _color = al_map_rgb(255, 0, 0);
    _minesSpawnTimer = std::make_shared<Timer>(Configs::_fps);
    _minesSpawnTimer->create();
    _minesSpawnTimer->startTimer();
}

MinesLauncher::~MinesLauncher()
{
    _minesSpawnTimer.reset();
    _mineSprite.reset();
    _mineExplosionSprite.reset();
}

void MinesLauncher::setWindowReference(Window *window) {
    _window = window; 
}

void MinesLauncher::setCollisionReference(CollisionHandler *collision) {
    _collision = collision; 
}

void MinesLauncher::removeMine(Mine *enemy)
{
    if (_mines.size() == 0)
        return;

    if (Configs::_isGameRunning)
        _mines.remove(enemy);
    else
        _mines.clear();
}

void MinesLauncher::runMineLauncher()
{
    loadSprites();
    while (Configs::_isGameRunning)
    {
        if (_window == nullptr || _collision == nullptr)
        {
            Thread::yield();
            continue;
        }

        processLoop();
        Thread::yield();
    }
}

void MinesLauncher::processLoop()
{
    if (_minesSpawnTimer->getCount() > _DELAY_MINE_SPAWN)
        createMine();
    handleMines();
}

void MinesLauncher::handleMines()
{
    for (auto mineItem = _mines.begin(); mineItem != _mines.end();)
    {
        Mine *mine = *mineItem;
        mineItem++;

        // Caso a mina já tenha sido destruída mas não foi removida ainda
        if (mine->getDead() || mine->isOutside())
            continue;

        // Caso a mina já esteja pronta para atacar
        if (mine->canFire())
        {
            // Executa o ataque
            mine->attack();
            for (int i = -500; i <= 500; i += 325)
            {
                for (int j = -500; j <= 500; j += 325)
                {
                    // Cria o tiro a adiciona nas listas
                    Laser *laser = new Laser(mine->Enemy::getPosition(), _color, Vector(i, j), false);
                    _collision->newEnemyShot(laser);
                    _window->addProjectile(laser);
                }
            }
        }
    }
}

void MinesLauncher::createMine()
{
    // Gera um ponto aleatório em y para a bomba aparecer
    Point point = Point(0, 0);
    point.rollRandom();
    point.x = Configs::_widthDisplay;

    // Cria uma mina
    Mine *mine = new Mine(point, Vector(-100, 0), _mineSprite, this);

    // Adiciona referência dela nas listas
    _mines.push_back(mine);
    _collision->newMine(mine);
    _window->addEnemy(mine);

    // Reset o timer
    _minesSpawnTimer->srsTimer();
}

void MinesLauncher::loadSprites()
{
    // Go to resources directory
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));

    _mineSprite = std::make_shared<Sprite>("spikebomb.png");
    _mineExplosionSprite = std::make_shared<Sprite>("explode.png");
    al_destroy_path(path);
}

__END_API