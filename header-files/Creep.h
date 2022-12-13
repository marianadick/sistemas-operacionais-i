#ifndef Creep_h
#define Creep_h

#include <memory>

#include "threads.h"
#include "traits.h"
#include "configs.h"
#include "Sprite.h"
#include "Enemy.h"
#include "Timer.h"
#include "Launcher.h"
#include "PurpleCreepLauncher.h"

__BEGIN_API

class Creep : public Enemy {
 public:
  Creep(Point point, Vector vector, std::shared_ptr<Sprite> creepSprite, ALLEGRO_COLOR color, Launcher * launcher);
  ~Creep();

  void draw();
  void update(double dt);
  void attack();

  /* Getters */
  ALLEGRO_COLOR getColor();
  int getSize();
  bool getFire();
  bool isOutOfBounds();
  double getAngle() {return _angle; };
  Vector getProjSpeed() {return _projSpeed; };
  Point getStop1() { return _stop1; }
  Point getStop2() { return _stop2; }
  Point getStop3() { return _stop3; }
  Point getStop4() { return _stop4; }

  /* Setters */
  void setSpeed(Vector speed) {_speed = speed; }
  void setAngle(double angle) {_angle = angle; };
  void setProjSpeed(Vector vector) {_projSpeed = vector; };
  void setStop1(Point point) { _stop1 = point; }
  void setStop2(Point point) { _stop2 = point; }
  void setStop3(Point point) { _stop3 = point; }
  void setStop4(Point point) { _stop4 = point; }

 /* White creep auxiliar variables */
  bool init = false;
  bool at1 = false;
  bool at2 = false;
  bool at3 = false;
  bool at4 = false;

 protected:
 private:
  void initializeTimer();

  /* Checks if enemy is able to fire */
  bool _fire;

  /* Shot delay */
  static int _ATTACK_DELAY;
  std::shared_ptr<Timer> _attackDelayTimer;

  /* Reference to its controller */
  Launcher *_launcher;

  /* Enemy sprites */
  std::shared_ptr<Sprite> _creepSprite;

  /* Color and timer of sprite */
  ALLEGRO_COLOR _color;

  /* Display limits (where to stop) */
  Point _stop1 = Point(725,50);
  Point _stop2 = Point(25,50);
  Point _stop3 = Point(25,550);
  Point _stop4 = Point(725,550);

  double _angle;
  Point _position;
  Vector _projSpeed = Vector(-400, 0);
};

__END_API

#endif