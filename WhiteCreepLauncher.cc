#include "header-files/WhiteCreepLauncher.h"

__BEGIN_API

WhiteCreepLauncher::WhiteCreepLauncher() {
  loadSprites();
  NEW_GROUP_DELAY = 60 * 15; // 5seg
  newGroupTimer = std::make_shared<Timer>(60);
  newGroupTimer->create();
  newGroupTimer->startTimer();
}

WhiteCreepLauncher::~WhiteCreepLauncher() {}

void WhiteCreepLauncher::attachWindow(Window * window) {
   _window = window; 
}

void WhiteCreepLauncher::attachCollision(CollisionHandler * collision) {
   _collisionHandler = collision; 
}
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

void WhiteCreepLauncher::createCreepGroup() {
    Point creepPosition = _window->_ship->getPosition();

    for(int i = 800; i <= 1000; i += 50) {
	    Creep * creep = new Creep(Point(i,300), Vector(-90, 0), purpleCreepSprite, al_map_rgb(255,254,253), this);
      _collisionHandler->newEnemyShip(creep);
      _window->addEnemy(creep);
      creeps.push_front(creep);
	 }

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

void WhiteCreepLauncher::createCreepBehavior() {
  for (auto creepItem = creeps.begin(); creepItem != creeps.end();) {
	Creep *creep = *creepItem;
	creepItem++;

  updateAngle(creep);
  //creep->rotateSprite();
  updateVector(creep);

	if (creep->getFire()) {
      // Chama o método attack do creep mas essa função aqui que vai lidar com a criação dos vetores
      creep->attack();

      Vector direcao;
      Point centro = Point(400, 300);
      Vector creepV = creep->getProjSpeed();
      Vector pointToCenter = Vector(centro.x - creep->getPosition().x, centro.y - creep->getPosition().y);

      if (pointToCenter.x > 0 && pointToCenter.y > 0)
        direcao = Vector(sqrt(pow(creepV.x, 2) + pow(pointToCenter.x, 2)), sqrt(pow(creepV.y, 2) + pow(pointToCenter.y, 2)));
      else if (pointToCenter.x > 0 && pointToCenter.y < 0)
        direcao = Vector(sqrt(pow(creepV.x, 2) + pow(pointToCenter.x, 2)), -sqrt(pow(creepV.y, 2) + pow(pointToCenter.y, 2)));
      else if (pointToCenter.x < 0 && pointToCenter.y > 0)
        direcao = Vector(-sqrt(pow(creepV.x, 2) + pow(pointToCenter.x, 2)), +sqrt(pow(creepV.y, 2) + pow(pointToCenter.y, 2)));
      else if (pointToCenter.x < 0 && pointToCenter.y < 0)
        direcao = Vector(-sqrt(pow(creepV.x, 2) + pow(pointToCenter.x, 2)), -sqrt(pow(creepV.y, 2) + pow(pointToCenter.y, 2)));

      auto *laser1 =
        new Laser(creep->getPosition(), creep->getColor(), direcao, false);

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

   if ((centre.x < stop1.x && centre.y > stop1.y && !(creep->init)))//initial 
   {
      vetor.flip();
      creep->setSpeed(vetor);
      creep->init=true;
   }

   if((centre.y<stop1.y)&& !creep->at1)//top right corner
   {
      vetor.flip();
      creep->setSpeed(vetor);
      creep->at1=true;
   }

   if((centre.x<stop2.x) && !creep->at2)//top left corner
   {
      vetor.flip();
      vetor.reflectY();
      creep->setSpeed(vetor);
      creep->at2=true;
   }

   if((centre.y > stop3.y) && !creep->at3)//bottom left
   {
      // speed.reflectY();
      vetor.flip();
      creep->setSpeed(vetor);
      creep->at3=true;
   }

   if((centre.x>stop4.x) && creep->at1 && creep->at2 && creep->at3)//bottom right
   {
      vetor.flip();
      vetor.reflectY();
      creep->setSpeed(vetor);
      creep->at1 = creep->at2 = creep->at3 = creep->at4 = false;
   }
}

__END_API