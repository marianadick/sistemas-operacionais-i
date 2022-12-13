#include "header-files/WhiteCreepLauncher.h"

__BEGIN_API

int WhiteCreepLauncher::_NEW_GROUP_DELAY = Configs::_fps * 11;

WhiteCreepLauncher::WhiteCreepLauncher() {
  _newGroupTimer = std::make_shared<Timer>(Configs::_fps);
  _newGroupTimer->create();
  _newGroupTimer->startTimer();
  loadSprites();
}

void WhiteCreepLauncher::runLauncher() {
  while (Configs::_isGameRunning) 
  {
    if (_window == nullptr || _collisionHandler == nullptr) {
      Thread::yield();
      continue;
    }

    if (_newGroupTimer->getCount() > _NEW_GROUP_DELAY) {
      createCreepGroup();
      _newGroupTimer->srsTimer();
    }

    createCreepBehavior();
    Thread::yield();
  }
}

void WhiteCreepLauncher::createCreepGroup() {
    Point creepPosition = _window->_ship->getPosition();

    for(int i = 800; i <= 1000; i += 50) {
	    Creep * creep = new Creep(Point(i,300), Vector(-90, 0), _whiteCreepSprite, al_map_rgb(255,254,253), this);
      _collisionHandler->newEnemyShip(creep);
      _window->addEnemy(creep);
      _creeps.push_front(creep);
	 }
  _newGroupTimer->srsTimer();
}

void WhiteCreepLauncher::createCreepBehavior() {
  for (auto creepItem = _creeps.begin(); creepItem != _creeps.end();) {
	Creep *creep = *creepItem;
	creepItem++;

  updateAngle(creep);
  updateVector(creep);

	if (creep->getFire()) {

      creep->attack();
      Vector shotDirection;
      Vector creepV = creep->getProjSpeed(); // Creep vector
      Point centre = Point(400, 300); // Center coordinates
      Vector pointToCenter = Vector(centre.x - creep->getPosition().x, centre.y - creep->getPosition().y);

      if (pointToCenter.x > 0 && pointToCenter.y > 0)
        shotDirection = Vector(sqrt(pow(creepV.x, 2) + pow(pointToCenter.x, 2)), sqrt(pow(creepV.y, 2) + pow(pointToCenter.y, 2)));
      else if (pointToCenter.x > 0 && pointToCenter.y < 0)
        shotDirection = Vector(sqrt(pow(creepV.x, 2) + pow(pointToCenter.x, 2)), -sqrt(pow(creepV.y, 2) + pow(pointToCenter.y, 2)));
      else if (pointToCenter.x < 0 && pointToCenter.y > 0)
        shotDirection = Vector(-sqrt(pow(creepV.x, 2) + pow(pointToCenter.x, 2)), +sqrt(pow(creepV.y, 2) + pow(pointToCenter.y, 2)));
      else if (pointToCenter.x < 0 && pointToCenter.y < 0)
        shotDirection = Vector(-sqrt(pow(creepV.x, 2) + pow(pointToCenter.x, 2)), -sqrt(pow(creepV.y, 2) + pow(pointToCenter.y, 2)));

      auto *laser1 = new Laser(creep->getPosition(), creep->getColor(), shotDirection, false);

      _collisionHandler->newEnemyShot(laser1);
      _window->addProjectile(laser1);
    }

    Point centre = creep->getPosition();
    centre = centre + creep->getProjSpeed() * 0.05;

    if (centre.y > 600 - 20 || centre.y < 20) {
      Vector speed = creep->getProjSpeed();
      speed.reflectY();
      creep->setProjSpeed(speed);
    }
  }
}

void WhiteCreepLauncher::updateAngle(Creep * creep)
{
   Point centre = creep->getPosition();
   Point delta;
   if(centre.x > 400)
   {
      delta.x = centre.x - 400;
      delta.y = centre.y - 300;
     
      creep->setAngle(atan(delta.y / delta.x));
   }
   else
   {
      delta.x = centre.x - 400;
      delta.y = centre.y - 300;
      creep->setAngle((delta.y / delta.x) + 3.14);
   }

   Vector vector = creep->getProjSpeed();
   vector.Angle(Point(400,300), centre, 0.5);
   creep->setProjSpeed(vector);
}

void WhiteCreepLauncher::updateVector(Creep * creep)
{
   Point centre = creep->getPosition();
   Point stop1 = creep->getStop1();
   Point stop2 = creep->getStop2();
   Point stop3 = creep->getStop3();
   Point stop4 = creep->getStop4();

   Vector vetor = creep->getVector();

   if ((centre.x < stop1.x && centre.y > stop1.y && !(creep->init))) 
   {
      vetor.flip();
      creep->setSpeed(vetor);
      creep->init=true;
   }

   if((centre.y<stop1.y)&& !creep->at1) // Top right corner
   {
      vetor.flip();
      creep->setSpeed(vetor);
      creep->at1=true;
   }

   if((centre.x<stop2.x) && !creep->at2) // Top left corner
   {
      vetor.flip();
      vetor.reflectY();
      creep->setSpeed(vetor);
      creep->at2=true;
   }

   if((centre.y > stop3.y) && !creep->at3) // Bottom left corner
   {
      vetor.flip();
      creep->setSpeed(vetor);
      creep->at3=true;
   }

   if((centre.x>stop4.x) && creep->at1 && creep->at2 && creep->at3) // Bottom right corner
   {
      vetor.flip();
      vetor.reflectY();
      creep->setSpeed(vetor);
      creep->at1 = creep->at2 = creep->at3 = creep->at4 = false;
   }
}

void WhiteCreepLauncher::removeCreep(Creep * creep) {
    if (_creeps.size() > 0)
      _creeps.remove(creep);
}

void WhiteCreepLauncher::attachWindow(Window * window) {
   _window = window; 
}

void WhiteCreepLauncher::attachCollision(CollisionHandler * collision) {
   _collisionHandler = collision; 
}

void WhiteCreepLauncher::loadSprites() {
  // Go to resources directory
  ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
  al_append_path_component(path, "resources");
  al_change_directory(al_path_cstr(path, '/'));
  _whiteCreepSprite = std::make_shared<Sprite>("EnemyBasic.png");
  al_destroy_path(path);
}

__END_API