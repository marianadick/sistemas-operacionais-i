#include "header-files/PurpleCreepLauncher.h"

__BEGIN_API

int PurpleCreepLauncher::_NEW_GROUP_DELAY = Configs::_fps * 7;

PurpleCreepLauncher::PurpleCreepLauncher()
{
  _newGroupTimer = std::make_shared<Timer>(60);
  _newGroupTimer->create();
  _newGroupTimer->startTimer();
  loadSprites();
}

void PurpleCreepLauncher::runLauncher()
{
  while (Configs::_isGameRunning)
  {
    if (_window == nullptr || _collisionHandler == nullptr)
    {
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
  Creep *creep1 = new Creep(Point(800, 300), Vector(-180, 0), _purpleCreepSprite, al_map_rgb(246, 64, 234), this);
  Creep *creep2 = new Creep(Point(900, 350), Vector(-180, 0), _purpleCreepSprite, al_map_rgb(246, 64, 234), this);
  Creep *creep3 = new Creep(Point(900, 250), Vector(-180, 0), _purpleCreepSprite, al_map_rgb(246, 64, 234), this);
  Creep *creep4 = new Creep(Point(1000, 400), Vector(-180, 0), _purpleCreepSprite, al_map_rgb(246, 64, 234), this);
  Creep *creep5 = new Creep(Point(1000, 200), Vector(-180, 0), _purpleCreepSprite, al_map_rgb(246, 64, 234), this);
  Creep *creep6 = new Creep(Point(1100, 100), Vector(-180, 0), _purpleCreepSprite, al_map_rgb(246, 64, 234), this);
  Creep *creep7 = new Creep(Point(1100, 500), Vector(-180, 0), _purpleCreepSprite, al_map_rgb(246, 64, 234), this);

  _collisionHandler->newEnemyShip(creep1);
  _collisionHandler->newEnemyShip(creep2);
  _collisionHandler->newEnemyShip(creep3);
  _collisionHandler->newEnemyShip(creep4);
  _collisionHandler->newEnemyShip(creep5);
  _collisionHandler->newEnemyShip(creep6);
  _collisionHandler->newEnemyShip(creep7);

  _window->addEnemy(creep1);
  _window->addEnemy(creep2);
  _window->addEnemy(creep3);
  _window->addEnemy(creep4);
  _window->addEnemy(creep5);
  _window->addEnemy(creep6);
  _window->addEnemy(creep7);

  _creeps.push_front(creep1);
  _creeps.push_front(creep2);
  _creeps.push_front(creep3);
  _creeps.push_front(creep4);
  _creeps.push_front(creep5);
  _creeps.push_front(creep6);
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