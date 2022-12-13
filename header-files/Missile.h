#ifndef MISSILE_H
#define MISSILE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>
#include <vector>

#include "configs.h"
#include "Projectile.h"

#include "traits.h"
#include "Point.h"
#include "Vector.h"
#include "Sprite.h"

__BEGIN_API

class Missile : public Projectile {
 public:
  Missile(Point point, ALLEGRO_COLOR color, Vector vector, bool isPlayerShot);
  ~Missile();

  void draw();
  void update(double dt);

  /* Getters*/
  int getDamage();
  bool wasDestroyed();
  int getSize();

  /* Projectile virtual method */
  void ackHitSomething() {};

 protected:
 private:

  double angle;

  /* Sprites */
  void loadSprites();
  int idx = 0;
  std::vector<std::shared_ptr<Sprite>> sprite;
  static int DAMAGE;
};

__END_API

#endif