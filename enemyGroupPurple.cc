#include "header-files/enemyGroupPurple.h"

__BEGIN_API

std::shared_ptr<Sprite> purpleShipSprite;

EnemyGroupPurple::EnemyGroupPurple()
{
    this->loadSprites();
    this->DELAY_SHIPS_SPAWN = 60* 5; // 5seg
    this->shipsSpawnTimer = std::make_shared<Timer>(60);
    this->shipsSpawnTimer->create();
    this->shipsSpawnTimer->startTimer();
}

EnemyGroupPurple::~EnemyGroupPurple() {}

void EnemyGroupPurple::setWindowReference(Window *window) { this->_window = window; }
void EnemyGroupPurple::setCollisionReference(Collision *collision) { this->_collision = collision; }
void EnemyGroupPurple::removeShip(EnemyPurple *enemy) { this->ships.remove(enemy); }

void EnemyGroupPurple::run()
{
    this->loadSprites();
    while (Configs::_isGameRunning)
    {
        if (this->_window == nullptr || this->_collision == nullptr)
        {
            Thread::yield();
            continue;
        }

        this->processLoop();
        Thread::yield();
    }
}

void EnemyGroupPurple::processLoop()
{
    // Há uma dependência aqui do timer ser maior do que o tempo para o ultimo sair da tela por causa de referência de ponteiros
    if (this->shipsSpawnTimer->getCount() > this->DELAY_SHIPS_SPAWN)
        this->createShips();
    this->handleShips();
}

void EnemyGroupPurple::handleShips()
{
    for (auto shipItem = this->ships.begin(); shipItem != this->ships.end();)
    {
        EnemyPurple *ship = *shipItem;
        shipItem++;

        if (ship->canFire())
        {
            // Chama o método attack do ship mas essa função aqui que vai lidar com a criação dos vetores
            ship->attack();

            int yVector = 60;
            if (this->shipsSpawnTimer->getCount() % 4 == 0)
                yVector = 100;
            else if (this->shipsSpawnTimer->getCount() % 5 == 0)
                yVector = 140;

            Laser *laser1 = new Laser(ship->getPosition(), ship->getColor(), ship->getVector() + Vector(-200, (-1 * yVector)), false);
            Laser *laser2 = new Laser(ship->getPosition(), ship->getColor(), ship->getVector() + Vector(-250, yVector), false);

            // this->_collision->addEnemiesShot(laser1);
            // this->_collision->addEnemiesShot(laser2);

            this->_window->addDrawableItem(laser1);
            this->_window->addDrawableItem(laser2);
        }
    }
}

void EnemyGroupPurple::createShips()
{
    // Cria os 5 ships purple
    EnemyPurple *ship1 = new EnemyPurple(Point(800, 300), Vector(-180, 0), this->purpleShipSprite, this->enemyExplosionSprite, this);
    EnemyPurple *ship2 = new EnemyPurple(Point(900, 350), Vector(-180, 0), this->purpleShipSprite, this->enemyExplosionSprite, this);
    EnemyPurple *ship3 = new EnemyPurple(Point(900, 250), Vector(-180, 0), this->purpleShipSprite, this->enemyExplosionSprite, this);
    EnemyPurple *ship4 = new EnemyPurple(Point(1000, 400), Vector(-180, 0), this->purpleShipSprite, this->enemyExplosionSprite, this);
    EnemyPurple *ship5 = new EnemyPurple(Point(1000, 200), Vector(-180, 0), this->purpleShipSprite, this->enemyExplosionSprite, this);
    EnemyPurple *ship6 = new EnemyPurple(Point(1100, 100), Vector(-180, 0), this->purpleShipSprite, this->enemyExplosionSprite, this);
    EnemyPurple *ship7 = new EnemyPurple(Point(1100, 500), Vector(-180, 0), this->purpleShipSprite, this->enemyExplosionSprite, this);

    // Manda para o objeto collision
    this->_collision->addEnemies(ship1);
    this->_collision->addEnemies(ship2);
    this->_collision->addEnemies(ship3);
    this->_collision->addEnemies(ship4);
    this->_collision->addEnemies(ship5);
    this->_collision->addEnemies(ship6);
    this->_collision->addEnemies(ship7);

    // Manda para o objeto window
    this->_window->addDrawableItem(ship1);
    this->_window->addDrawableItem(ship2);
    this->_window->addDrawableItem(ship3);
    this->_window->addDrawableItem(ship4);
    this->_window->addDrawableItem(ship5);
    this->_window->addDrawableItem(ship6);
    this->_window->addDrawableItem(ship7);

    // Guarda na referência dos ships
    this->ships.push_front(ship1);
    this->ships.push_front(ship2);
    this->ships.push_front(ship3);
    this->ships.push_front(ship4);
    this->ships.push_front(ship5);
    this->ships.push_front(ship6);
    this->ships.push_front(ship7);

    // Reset o timer
    this->shipsSpawnTimer->srsTimer();
}

void PurpleEnemiesControl::loadSprites()
{
    // Go to resources directory
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));

    this->purpleShipSprite = std::make_shared<Sprite>("EnemyBasic.png");
    this->enemyExplosionSprite = std::make_shared<Sprite>("explode.png");
    al_destroy_path(path);
}

__END_API