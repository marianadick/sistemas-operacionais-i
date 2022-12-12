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
};

__END_API

#endif