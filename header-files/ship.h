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
  void hit(int damage);
  int getSize();
  Point getPosition();
  bool getDead();

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
  void loadSprites();
  void drawHealthBar();

  static int SHIP_SPEED;
  static int SHIP_SIZE;
  static int LASER_DELAY;
  static int MISSILE_DELAY;
  
  static ALLEGRO_COLOR SHIP_COLOR;

  /* Ship position */
  float _life = 5;
  float _health = 3;
  bool _dead = false;
  int _row;            /**<row of animation to be played */
  int _col;            /**< column of animation to be played */
  Point _position;
  Vector _speed;
  std::shared_ptr<Sprite> _sprite;

  /* Reference to game state and obj*/
  Input *_kb;
  Window *_window;
  CollisionHandler *_collisionHandler;

  std::shared_ptr<Timer> laserDelayTimer;
  std::shared_ptr<Timer> missileDelayTimer;
};

__END_API

#endif