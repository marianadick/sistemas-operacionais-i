#ifndef PurpleCreep_h
#define PurpleCreep_h

#include <memory>

#include "threads.h"
#include "traits.h"
#include "configs.h"
#include "Sprite.h"
#include "Enemy.h"
#include "Timer.h"
#include "PurpleCreepLauncher.h"

__BEGIN_API

class PurpleCreepLauncher;

class PurpleCreep : public Enemy {
 public:
  PurpleCreep(Point point, Vector vector, std::shared_ptr<Sprite> shipSprite,
			  std::shared_ptr<Sprite> deathSprite, PurpleCreepLauncher *purpleCreepLauncher);
  ~PurpleCreep();

  void draw();
  void update(double dt);
  void attack();

  /* Getters */
  ALLEGRO_COLOR getColor();
  int getSize();
  bool setFire();
  bool isOutOfBounds();

 protected:
 private:
  void initializeTimer();
  /* Checks if enemy is able to fire */
  bool _fire;

  /* Shot delay */
  static int _SHOTS_DELAY;
  std::shared_ptr<Timer> _shotsTimer;

  /* Reference to its controller */
  PurpleCreepLauncher *_purpleCreepLauncher;

  /* Enemy sprites */
  std::shared_ptr<Sprite> _shipSprite;
  std::shared_ptr<Sprite> _deathSprite;

  /* Color and timer of sprite */
  ALLEGRO_COLOR _color;
  int _deathSpriteTimer;
};

__END_API

#endif