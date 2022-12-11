#include "header-files/PurpleCreepLauncher.h"

__BEGIN_API

std::shared_ptr<Sprite> purpleShipSprite;

PurpleCreepLauncher::PurpleCreepLauncher() {
  loadSprites();
  DELAY_SHIPS_SPAWN = 60 * 5; // 5seg
  shipsSpawnTimer = std::make_shared<Timer>(60);
  shipsSpawnTimer->create();
  shipsSpawnTimer->startTimer();
}

PurpleCreepLauncher::~PurpleCreepLauncher() {}

void PurpleCreepLauncher::attachWindow(Window *window) { _window = window; }
void PurpleCreepLauncher::attachCollision(CollisionHandler *collision) { _collision = collision; }
void PurpleCreepLauncher::removeShip(PurpleCreep *enemy) { ships.remove(enemy); }

void PurpleCreepLauncher::run() {
  loadSprites();
  while (Configs::_isGameRunning) {
	if (_window == nullptr || _collision == nullptr) {
	  Thread::yield();
	  continue;
	}

	processLoop();
	Thread::yield();
  }
}

void PurpleCreepLauncher::processLoop() {
  // Há uma dependência aqui do timer ser maior do que o tempo para o ultimo sair da tela por causa de referência de ponteiros
  if (shipsSpawnTimer->getCount() > DELAY_SHIPS_SPAWN)
	createShips();
  handleShips();
}

void PurpleCreepLauncher::handleShips() {
  for (auto shipItem = ships.begin(); shipItem != ships.end();) {
	PurpleCreep *ship = *shipItem;
	shipItem++;

	if (ship->setFire()) {
	  // Chama o método attack do ship mas essa função aqui que vai lidar com a criação dos vetores
	  ship->attack();

	  int yVector = 60;
	  if (shipsSpawnTimer->getCount() % 4 == 0)
		yVector = 100;
	  else if (shipsSpawnTimer->getCount() % 5 == 0)
		yVector = 140;

	  auto *laser1 =
		  new Laser(ship->getPosition(), ship->getColor(), ship->getVector() + Vector(-200, (-1 * yVector)), false);
	  auto *laser2 = new Laser(ship->getPosition(), ship->getColor(), ship->getVector() + Vector(-250, yVector), false);

	  _collision->newEnemyShot(laser1);
	  _collision->newEnemyShot(laser2);

	  _window->addProjectile(laser1);
	  _window->addProjectile(laser2);
	}
  }
}

void PurpleCreepLauncher::createShips() {
  // Cria os 5 ships purple
  auto *ship1 = new PurpleCreep(Point(800, 300), Vector(-180, 0), purpleShipSprite, enemyExplosionSprite, this);
  auto *ship2 = new PurpleCreep(Point(900, 350), Vector(-180, 0), purpleShipSprite, enemyExplosionSprite, this);
  auto *ship3 = new PurpleCreep(Point(900, 250), Vector(-180, 0), purpleShipSprite, enemyExplosionSprite, this);
  auto *ship4 = new PurpleCreep(Point(1000, 400), Vector(-180, 0), purpleShipSprite, enemyExplosionSprite, this);
  auto *ship5 = new PurpleCreep(Point(1000, 200), Vector(-180, 0), purpleShipSprite, enemyExplosionSprite, this);
  auto *ship6 = new PurpleCreep(Point(1100, 100), Vector(-180, 0), purpleShipSprite, enemyExplosionSprite, this);
  auto *ship7 = new PurpleCreep(Point(1100, 500), Vector(-180, 0), purpleShipSprite, enemyExplosionSprite, this);

  // Manda para o objeto collision
  _collision->newEnemyShip(ship1);
  _collision->newEnemyShip(ship2);
  _collision->newEnemyShip(ship3);
  _collision->newEnemyShip(ship4);
  _collision->newEnemyShip(ship5);
  _collision->newEnemyShip(ship6);
  _collision->newEnemyShip(ship7);

  // Manda para o objeto window
  _window->addEnemy(ship1);
  _window->addEnemy(ship2);
  _window->addEnemy(ship3);
  _window->addEnemy(ship4);
  _window->addEnemy(ship5);
  _window->addEnemy(ship6);
  _window->addEnemy(ship7);

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

void PurpleCreepLauncher::loadSprites() {
  // Go to resources directory
  ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
  al_append_path_component(path, "resources");
  al_change_directory(al_path_cstr(path, '/'));

  purpleShipSprite = std::make_shared<Sprite>("EnemyBasic.png");
  enemyExplosionSprite = std::make_shared<Sprite>("explode.png");
  al_destroy_path(path);
}

__END_API