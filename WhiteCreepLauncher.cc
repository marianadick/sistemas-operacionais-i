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

  updateAngle(ship);
  updateVector(ship);

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


    // Point pt = Point(800, 200);
    // Point point1 = Point(800, 500);
    // Point point2 = Point(800, 580);
    // Point point3 = Point(850, 300);
    // Vector vector1 = Vector(0, 0);

    for(int i = 800; i <= 1000; i += 50) {
	    Creep * creep = new Creep(Point(i,300), Vector(-90, 0), purpleCreepSprite, al_map_rgb(255,254,253), this);
      creep->stop1 = Point(700,100);
      creep->stop2 = Point(100,100);
      creep->stop3 = Point(100,500);
      creep->stop4 = Point(700,500);
      _collisionHandler->newEnemyShip(creep);
      _window->addEnemy(creep);
      creeps.push_front(creep);

	 }

    // pt.rollRandom();
    // vector1.rollRandom();
    // Creep * creep1 = new Creep(pt, vector1, purpleCreepSprite, al_map_rgb(255, 255, 255), this);
    // pt.rollRandom();
    // vector1.rollRandom();
    // Creep * creep2 = new Creep(pt, vector1, purpleCreepSprite, al_map_rgb(255, 255, 255), this);
    // pt.rollRandom();
    // vector1.rollRandom();
    // Creep * creep3 = new Creep(pt, vector1, purpleCreepSprite, al_map_rgb(255, 255, 255), this);

//     vector1.Angle(shipPosition, point1, 1);

//   Creep * creep1 = new Creep(point1, vector1, purpleCreepSprite, al_map_rgb(255, 255, 255), this);
//   vector1.Angle(shipPosition, point2, 1);
//   Creep * creep2 = new Creep(point2, vector1, purpleCreepSprite, al_map_rgb(255, 255, 255), this);
//   vector1.Angle(shipPosition, point3, 1);
//   Creep * creep3 = new Creep(point3, vector1, purpleCreepSprite, al_map_rgb(255, 255, 255), this);


  // Manda para o objeto collision
  // _collisionHandler->newEnemyShip(creep1);
  // _collisionHandler->newEnemyShip(creep2);
  // _collisionHandler->newEnemyShip(creep3);

  // // Manda para o objeto window
  // this->_window->addEnemy(creep1);
  // this->_window->addEnemy(creep2);
  // this->_window->addEnemy(creep3);

  // creeps.push_front(creep1);
  // creeps.push_front(creep2);
  // creeps.push_front(creep3);

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

void WhiteCreepLauncher::updateAngle(Creep * creep)
{
   Point centre = creep->getPosition();
   Point delta;
   if(centre.x>400)
   {
      delta.x=centre.x-400;
      delta.y=centre.y-300;
     
      creep->setAngle(atan(delta.y/delta.x));
   }
   else
   {
      delta.x=centre.x-400;
      delta.y=centre.y-300;
      creep->setAngle((delta.y/delta.x)+3.14);
   }

   Vector vector1 = creep->getProjSpeed();
   vector1.Angle(Point(400,300), centre, 0.5);
    creep->setProjSpeed(vector1);
}

void WhiteCreepLauncher::updateVector(Creep * creep)
{
   Point centre = creep->getPosition();
   Point stop1 = creep->getStop1();
   Point stop2 = creep->getStop2();
   Point stop3 = creep->getStop3();
   Point stop4 = creep->getStop4();

   if ((centre.x < stop1.x && centre.y > stop1.y && !(creep->init)))//initial 
   {
      Vector vector2 = creep->getVector();
      vector2.flip();
      creep->setSpeed(vector2);
      creep->init=true;
   }

   
   if((centre.y<stop1.y)&& !creep->at1)//top right corner
   {
      std::cout<<"1 is true";
      Vector vector2 = creep->getVector();
      vector2.flip();
      creep->setSpeed(vector2);
      creep->at1=true;
   }
   if((centre.x<stop2.x) && !creep->at2)//top left corner
   {
      std::cout<<"2 is true";
      Vector vector2 = creep->getVector();
      vector2.flip();
      vector2.reflectY();
      creep->setSpeed(vector2);
      creep->at2=true;
   }
   if((centre.y > stop3.y) && !creep->at3)//bottom left
   {
      std::cout<<"3 is true";
      // speed.reflectY();
      Vector vector2 = creep->getVector();
      vector2.flip();
      creep->setSpeed(vector2);
      creep->at3=true;
   }
   if((centre.x>stop4.x) && creep->at1 && creep->at2 && creep->at3)//bottom right
   {
      std::cout<<"4 is true";
      Vector vector2 = creep->getVector();
      vector2.flip();
      vector2.reflectY();
      creep->setSpeed(vector2);
      creep->at1=creep->at2=creep->at3=creep->at4=false;
   }
}

__END_API