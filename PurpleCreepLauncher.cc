#include "header-files/PurpleCreepLauncher.h"

__BEGIN_API

int PurpleCreepLauncher::_NEW_GROUP_DELAY = Configs::_fps * 8;

PurpleCreepLauncher::PurpleCreepLauncher()
{
  _newGroupTimer = std::make_shared<Timer>(Configs::_fps);
  _newGroupTimer->create();
  _newGroupTimer->startTimer();
  loadSprites();
}

void PurpleCreepLauncher::runLauncher()
{
  while (Configs::_isGameRunning)
  {
    if (_window == nullptr || _collisionHandler == nullptr) {
      Thread::yield();
      continue;
    }

    if (_newGroupTimer->getCount() > _NEW_GROUP_DELAY)
    {
      createCreepGroup();
      _newGroupTimer->srsTimer();
    }
    
    createCreepBehavior();
    Thread::yield();
  }
}

void PurpleCreepLauncher::createCreepBehavior()
{
  for (auto creeps = _creeps.begin(); creeps != _creeps.end();)
  {
    Creep *creep = *creeps;
    creeps++;

    if (creep->getFire())
    {
      creep->attack();

      int yVector = 60;
      if (_newGroupTimer->getCount() % 4 == 0)
        yVector = 100;
      else if (_newGroupTimer->getCount() % 5 == 0)
        yVector = 140;

      auto *laser1 = new Laser(creep->getPosition(), creep->getColor(), 
                               creep->getVector() + Vector(-200, (-1 * yVector)), false);
      auto *laser2 = new Laser(creep->getPosition(), creep->getColor(), 
                               creep->getVector() + Vector(-250, yVector), false);

      _collisionHandler->newEnemyShot(laser1);
      _collisionHandler->newEnemyShot(laser2);

      _window->addProjectile(laser1);
      _window->addProjectile(laser2);
    }
  }
}

void PurpleCreepLauncher::createCreepGroup()
{
  Point p1 = Point( 800, 300); Point p2 = Point( 900, 250);
  Point p3 = Point( 900, 350); Point p4 = Point(1000, 200);
  Point p5 = Point(1000, 400); Point p6 = Point(1100, 100);
  Point p7 = Point(1100, 500);

  Vector vetor = Vector(-180, 0);
  ALLEGRO_COLOR color = al_map_rgb(246, 64, 234);

  Creep *creep1 = new Creep(p1, vetor, _purpleCreepSprite, color, this);
  Creep *creep2 = new Creep(p2, vetor, _purpleCreepSprite, color, this);
  Creep *creep3 = new Creep(p3, vetor, _purpleCreepSprite, color, this);
  Creep *creep4 = new Creep(p4, vetor, _purpleCreepSprite, color, this);
  Creep *creep5 = new Creep(p5, vetor, _purpleCreepSprite, color, this);
  Creep *creep6 = new Creep(p6, vetor, _purpleCreepSprite, color, this);
  Creep *creep7 = new Creep(p7, vetor, _purpleCreepSprite, color, this);

  _window->addEnemy(creep1); _window->addEnemy(creep2);
  _window->addEnemy(creep3); _window->addEnemy(creep4);
  _window->addEnemy(creep5); _window->addEnemy(creep6);
  _window->addEnemy(creep7);

  _collisionHandler->newEnemyShip(creep1); _collisionHandler->newEnemyShip(creep2);
  _collisionHandler->newEnemyShip(creep3); _collisionHandler->newEnemyShip(creep4);
  _collisionHandler->newEnemyShip(creep5); _collisionHandler->newEnemyShip(creep6);
  _collisionHandler->newEnemyShip(creep7);

  _creeps.push_front(creep1); _creeps.push_front(creep2);
  _creeps.push_front(creep3); _creeps.push_front(creep4);
  _creeps.push_front(creep5); _creeps.push_front(creep6);
  _creeps.push_front(creep7);

  _newGroupTimer->srsTimer();
}

void PurpleCreepLauncher::loadSprites()
{
  // Go to resources directory
  ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
  al_append_path_component(path, "resources");
  al_change_directory(al_path_cstr(path, '/'));
  _purpleCreepSprite = std::make_shared<Sprite>("EnemyBasic.png");
  al_destroy_path(path);
}

void PurpleCreepLauncher::removeCreep(Creep *creep)
{
  if (_creeps.size())
    _creeps.remove(creep);
}

void PurpleCreepLauncher::attachWindow(Window *window)
{
  _window = window;
}

void PurpleCreepLauncher::attachCollision(CollisionHandler *collision)
{
  _collisionHandler = collision;
}

__END_API