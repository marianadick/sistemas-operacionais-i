#include "header-files/PurpleCreepLauncher.h"

__BEGIN_API

PurpleCreepLauncher::PurpleCreepLauncher() {
  loadSprites();
  NEW_GROUP_DELAY = 60 * 5; // 5seg
  newGroupTimer = std::make_shared<Timer>(60);
  newGroupTimer->create();
  newGroupTimer->startTimer();
}

PurpleCreepLauncher::~PurpleCreepLauncher() {}

void PurpleCreepLauncher::attachWindow(Window * window) { _window = window; }
void PurpleCreepLauncher::attachCollision(CollisionHandler * collision) { _collisionHandler = collision; }
void PurpleCreepLauncher::removeCreep(Creep * creep) {
      if (this->creeps.size() > 0)
        this->creeps.remove(creep);
}

void PurpleCreepLauncher::runLauncher() {
  while (Configs::_isGameRunning) {
	if (_window == nullptr || _collisionHandler == nullptr) {
	  Thread::yield();
	}

	if (newGroupTimer->getCount() > NEW_GROUP_DELAY) {
    createCreepGroup();
    newGroupTimer->srsTimer();
  }
  createCreepBehavior();
	Thread::yield();
  }
}

void PurpleCreepLauncher::createCreepBehavior() {
  for (auto shipItem = creeps.begin(); shipItem != creeps.end();) {
	Creep *ship = *shipItem;
	shipItem++;

	if (ship->getFire()) {
	  // Chama o método attack do ship mas essa função aqui que vai lidar com a criação dos vetores
	  ship->attack();

	  int yVector = 60;
	  if (newGroupTimer->getCount() % 4 == 0)
		yVector = 100;
	  else if (newGroupTimer->getCount() % 5 == 0)
		yVector = 140;

	  auto *laser1 =
		  new Laser(ship->getPosition(), ship->getColor(), ship->getVector() + Vector(-200, (-1 * yVector)), false);
	  auto *laser2 = new Laser(ship->getPosition(), ship->getColor(), ship->getVector() + Vector(-250, yVector), false);

	  _collisionHandler->newEnemyShot(laser1);
	  _collisionHandler->newEnemyShot(laser2);

	  _window->addProjectile(laser1);
	  _window->addProjectile(laser2);
	}
  }
}

void PurpleCreepLauncher::createCreepGroup() {
  Creep * creep1 = new Creep(Point(800, 300), Vector(-180, 0), purpleCreepSprite, al_map_rgb(246, 64, 234), this);
  Creep * creep2 = new Creep(Point(900, 350), Vector(-180, 0), purpleCreepSprite, al_map_rgb(246, 64, 234), this);
  Creep * creep3 = new Creep(Point(900, 250), Vector(-180, 0), purpleCreepSprite, al_map_rgb(246, 64, 234), this);
  Creep * creep4 = new Creep(Point(1000, 400), Vector(-180, 0), purpleCreepSprite, al_map_rgb(246, 64, 234), this);
  Creep * creep5 = new Creep(Point(1000, 200), Vector(-180, 0), purpleCreepSprite, al_map_rgb(246, 64, 234), this);
  Creep * creep6 = new Creep(Point(1100, 100), Vector(-180, 0), purpleCreepSprite, al_map_rgb(246, 64, 234), this);
  Creep * creep7 = new Creep(Point(1100, 500), Vector(-180, 0), purpleCreepSprite, al_map_rgb(246, 64, 234), this);

  // Manda para o objeto collision
  _collisionHandler->newEnemyShip(creep1);
  _collisionHandler->newEnemyShip(creep2);
  _collisionHandler->newEnemyShip(creep3);
  _collisionHandler->newEnemyShip(creep4);
  _collisionHandler->newEnemyShip(creep5);
  _collisionHandler->newEnemyShip(creep6);
  _collisionHandler->newEnemyShip(creep7);

  // Manda para o objeto window
  this->_window->addEnemy(creep1);
  this->_window->addEnemy(creep2);
  this->_window->addEnemy(creep3);
  this->_window->addEnemy(creep4);
  this->_window->addEnemy(creep5);
  this->_window->addEnemy(creep6);
  this->_window->addEnemy(creep7);

  creeps.push_front(creep1);
  creeps.push_front(creep2);
  creeps.push_front(creep3);
  creeps.push_front(creep4);
  creeps.push_front(creep5);
  creeps.push_front(creep6);
  creeps.push_front(creep7);

  // Reset o timer
  newGroupTimer->srsTimer();
}

void PurpleCreepLauncher::loadSprites() {
  // Go to resources directory
  ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
  al_append_path_component(path, "resources");
  al_change_directory(al_path_cstr(path, '/'));
  purpleCreepSprite = std::make_shared<Sprite>("EnemyBasic.png");
  al_destroy_path(path);
}

__END_API