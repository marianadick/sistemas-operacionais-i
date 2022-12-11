#include "header-files/enemyGroupPurple.h"

__BEGIN_API

std::shared_ptr<Sprite> purpleShipSprite;

EnemyGroupPurple::EnemyGroupPurple()
{
    loadSprites();
    DELAY_SHIPS_SPAWN = 60* 5; // 5seg
    shipsSpawnTimer = std::make_shared<Timer>(60);
    shipsSpawnTimer->create();
    shipsSpawnTimer->startTimer();
}

EnemyGroupPurple::~EnemyGroupPurple() {}

void EnemyGroupPurple::setWindowReference(Window *window) { _window = window; }
void EnemyGroupPurple::setCollisionReference(Collision *collision) { _collision = collision; }
void EnemyGroupPurple::removeShip(EnemyPurple *enemy) { ships.remove(enemy); }

void EnemyGroupPurple::run()
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

void EnemyGroupPurple::processLoop()
{
    // Há uma dependência aqui do timer ser maior do que o tempo para o ultimo sair da tela por causa de referência de ponteiros
    if (shipsSpawnTimer->getCount() > DELAY_SHIPS_SPAWN)
        createShips();
    handleShips();
}

void EnemyGroupPurple::handleShips()
{
    for (auto shipItem = ships.begin(); shipItem != ships.end();)
    {
        EnemyPurple *ship = *shipItem;
        shipItem++;

        if (ship->canFire())
        {
            // Chama o método attack do ship mas essa função aqui que vai lidar com a criação dos vetores
            ship->attack();

            int yVector = 60;
            if (shipsSpawnTimer->getCount() % 4 == 0)
                yVector = 100;
            else if (shipsSpawnTimer->getCount() % 5 == 0)
                yVector = 140;

            Laser *laser1 = new Laser(ship->getPosition(), ship->getColor(), ship->getVector() + Vector(-200, (-1 * yVector)), false);
            Laser *laser2 = new Laser(ship->getPosition(), ship->getColor(), ship->getVector() + Vector(-250, yVector), false);

            _collision->newEnemyShot(laser1);
            _collision->newEnemyShot(laser2);

            _window->addDrawableItem(laser1);
            _window->addDrawableItem(laser2);
        }
    }
}

void EnemyGroupPurple::createShips()
{
    // Cria os 5 ships purple
    EnemyPurple *ship1 = new EnemyPurple(Point(800, 300), Vector(-180, 0), purpleShipSprite, enemyExplosionSprite, this);
    EnemyPurple *ship2 = new EnemyPurple(Point(900, 350), Vector(-180, 0), purpleShipSprite, enemyExplosionSprite, this);
    EnemyPurple *ship3 = new EnemyPurple(Point(900, 250), Vector(-180, 0), purpleShipSprite, enemyExplosionSprite, this);
    EnemyPurple *ship4 = new EnemyPurple(Point(1000, 400), Vector(-180, 0), purpleShipSprite, enemyExplosionSprite, this);
    EnemyPurple *ship5 = new EnemyPurple(Point(1000, 200), Vector(-180, 0), purpleShipSprite, enemyExplosionSprite, this);
    EnemyPurple *ship6 = new EnemyPurple(Point(1100, 100), Vector(-180, 0), purpleShipSprite, enemyExplosionSprite, this);
    EnemyPurple *ship7 = new EnemyPurple(Point(1100, 500), Vector(-180, 0), purpleShipSprite, enemyExplosionSprite, this);

    // Manda para o objeto collision
    _collision->newEnemyShip(ship1);
    _collision->newEnemyShip(ship2);
    _collision->newEnemyShip(ship3);
    _collision->newEnemyShip(ship4);
    _collision->newEnemyShip(ship5);
    _collision->newEnemyShip(ship6);
    _collision->newEnemyShip(ship7);

    // Manda para o objeto window
    _window->addDrawableItem(ship1);
    _window->addDrawableItem(ship2);
    _window->addDrawableItem(ship3);
    _window->addDrawableItem(ship4);
    _window->addDrawableItem(ship5);
    _window->addDrawableItem(ship6);
    _window->addDrawableItem(ship7);

    // Guarda na referência dos ships
    ships.push_front(ship1);
    ships.push_front(ship2);
    ships.push_front(ship3);
    ships.push_front(ship4);
    ships.push_front(ship5);
    ships.push_front(ship6);
    ships.push_front(ship7);

    // Reset o timer
    shipsSpawnTimer->srsTimer();
}

void EnemyGroupPurple::loadSprites()
{
    // Go to resources directory
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));

    purpleShipSprite = std::make_shared<Sprite>("EnemyBasic.png");
    enemyExplosionSprite = std::make_shared<Sprite>("explode.png");
    al_destroy_path(path);
}

__END_API