#ifndef window_h
#define window_h

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include <memory>
#include <list>

#include "traits.h"
#include "thread.h"
#include "ship.h"
#include "input.h"
#include "configs.h"
#include "Vector.h"
#include "Sprite.h"
#include "Enemy.h"
#include "Projectile.h"

__BEGIN_API
class Ship;
class Input;

class Window {
 public:
  Window();
  Window(int w, int h, int fps);
  ~Window();

  void runWindow();

  // Should add / remove enemies to be drawn
  void addEnemy(Enemy *enemy);
  void removeEnemy(Enemy *enemy);

  // Should add / remove projectiles to be drawn
  void addProjectile(Projectile *projectile);
  void removeProjectile(Projectile *projectile);

  void attachShip(Ship *ship); // Link ship to window
  void attachKb(Input *kb); // Link keyboard to window (QUIT game)

  Ship *_ship;

 protected:
 private:
  /* Lists of variable elements to draw */
  std::list<Enemy *> enemies;
  std::list<Projectile *> projectiles;

  /* Window's main logic */
  void checkEvent();
  void drawWindow();
  void updateBg(double dt);
  void loadSprites();

  /* Helper functions to draw and update variable elements */
  void drawEnemies(double dt);
  void drawProjectiles(double dt);
  void drawShipLives();

  /* Display parameters */
  int _widthDisplay;
  int _heightDisplay;
  int _fps;

  // Background
  Point _bgMid; /**<point used by the background to draw from */
  Point _fgMid;
  Point _fg2Mid;
  Vector _bgSpeed; /**<background movement speed */
  Vector _fgSpeed;
  std::shared_ptr<Sprite> _bgSprite; /**<shared pointer to background animation */
  std::shared_ptr<Sprite> _fgSprite;

  /* Allegro related */
  ALLEGRO_DISPLAY *_display;
  ALLEGRO_TIMER *_timer;
  ALLEGRO_EVENT_QUEUE *_eventQueue;

  /* Time */
  float _prevTime;

  /* Reference to the keyboard */
  Input *_kb;
};

__END_API

#endif