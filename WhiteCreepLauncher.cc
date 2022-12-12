#include "header-files/WhiteCreepLauncher.h"

__BEGIN_API

WhiteCreepLauncher::WhiteCreepLauncher() {
  loadSprites();
  NEW_GROUP_DELAY = 60 * 7; // 5seg
  newGroupTimer = std::make_shared<Timer>(60);
  newGroupTimer->create();
  newGroupTimer->startTimer();
}

WhiteCreepLauncher::~WhiteCreepLauncher() {}

void WhiteCreepLauncher::attachWindow(Window * window) { _window = window; }
void WhiteCreepLauncher::attachCollision(CollisionHandler * collision) { _collisionHandler = collision; }
void WhiteCreepLauncher::removeCreep(Creep * creep) {
      if (this->creeps.size() > 0)
        this->creeps.remove(creep);
}

void WhiteCreepLauncher::runLauncher() {
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

void WhiteCreepLauncher::createCreepBehavior() {
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

void WhiteCreepLauncher::createCreepGroup() {
    Point shipPosition = _window->_ship->getPosition();

    Point point1 = Point(800, 500);
    Point point2 = Point(800, 580);
    Point point3 = Point(850, 300);
    Vector vector1 = Vector(0, 0);
    vector1.Angle(shipPosition, point1, 1);

  Creep * creep1 = new Creep(point1, vector1, purpleCreepSprite, al_map_rgb(255, 255, 255), this);
  vector1.Angle(shipPosition, point2, 1);
  Creep * creep2 = new Creep(point2, vector1, purpleCreepSprite, al_map_rgb(255, 255, 255), this);
  vector1.Angle(shipPosition, point3, 1);
  Creep * creep3 = new Creep(point3, vector1, purpleCreepSprite, al_map_rgb(255, 255, 255), this);


  // Manda para o objeto collision
  _collisionHandler->newEnemyShip(creep1);
  _collisionHandler->newEnemyShip(creep2);
  _collisionHandler->newEnemyShip(creep3);

  // Manda para o objeto window
  this->_window->addEnemy(creep1);
  this->_window->addEnemy(creep2);
  this->_window->addEnemy(creep3);

  creeps.push_front(creep1);
  creeps.push_front(creep2);
  creeps.push_front(creep3);

  // Reset o timer
  newGroupTimer->srsTimer();
}

void WhiteCreepLauncher::loadSprites() {
  // Go to resources directory
  ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
  al_append_path_component(path, "resources");
  al_change_directory(al_path_cstr(path, '/'));
  purpleCreepSprite = std::make_shared<Sprite>("EnemyBasic.png");
  al_destroy_path(path);
}

__END_API