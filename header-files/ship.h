#ifndef ship_h
#define ship_h

#include <memory>

#include "thread.h"
#include "traits.h"
#include "configs.h"
#include "input.h"
#include "window.h"
#include "Missile.h"
#include "Point.h"
#include "Vector.h"
#include "Sprite.h"
#include "Action.h"
#include "Laser.h"
#include "Timer.h"
#include "CollisionHandler.h"

__BEGIN_API

class CollisionHandler;

class Ship : public Drawable {
 public:
  Ship();
  Ship(Input *kb);
  ~Ship();

  void runShip();
  void getInputKb();
  int getShipLives();
  int getSize();
  Point getPosition();
  bool getDead();

  void hit(int damage);
  void draw();
  void update(double dt);

  void attachWindow(Window * window);
  void attachCollision(CollisionHandler * collisionHandler);

 protected:
 private:
  void initializeTimers();
  void selectShipAnimation();
  void checkBoundary();
  void shootLaser();
  void shootMissile();
  void drawHealthBar();
  void loadSprites();

  static int SHIP_SPEED;
  static int SHIP_SIZE;
  static int LASER_DELAY;
  static int MISSILE_DELAY;
  
  static ALLEGRO_COLOR SHIP_COLOR;

  /* Ship position */
  int _row;
  int _col;
  Point _position;
  Vector _speed;

  /* Ship state and health */
  float _life = 5;
  float _health = 3;
  bool _dead = false;

  std::shared_ptr<Sprite> _sprite;

  /* Reference to input, window and collisionHandler */
  Input *_kb;
  Window *_window;
  CollisionHandler *_collisionHandler;

  /* Delays */
  std::shared_ptr<Timer> laserDelayTimer;
  std::shared_ptr<Timer> missileDelayTimer;
};

__END_API

#endif