#include "header-files/Missile.h"

__BEGIN_API

Missile::Missile(Point point, ALLEGRO_COLOR color, Vector speed, bool isPlayerShot) : Projectile(point,
																								 color,
																								 speed,
																								 isPlayerShot) {
	angle = atan(speed.y / speed.x) + 4.71 * -1;
  _point = _point + _speed * 0.1; 
  loadSprites();
}

Missile::~Missile() {
  sprite.clear();
}

void Missile::draw() {
  Missile::sprite[idx]->draw_rotated(_point, angle, 0);
  idx++;
  if (idx > 7)
	idx = 0;
}

void Missile::update(double dt) {
  _point = _point + _speed * dt;
}

bool Missile::wasDestroyed() {
   return false; 
}

int Missile::getDamage() {
   return 3; 
}

int Missile::getSize() {
   return 4; 
}

void Missile::loadSprites() {
  ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
  al_append_path_component(path, "resources");
  al_change_directory(al_path_cstr(path, '/'));

  Missile::sprite.push_back(std::make_shared<Sprite>("m1.png"));
  Missile::sprite.push_back(std::make_shared<Sprite>("m2.png"));
  Missile::sprite.push_back(std::make_shared<Sprite>("m3.png"));
  Missile::sprite.push_back(std::make_shared<Sprite>("m4.png"));
  Missile::sprite.push_back(std::make_shared<Sprite>("m5.png"));
  Missile::sprite.push_back(std::make_shared<Sprite>("m6.png"));
  Missile::sprite.push_back(std::make_shared<Sprite>("m7.png"));
  Missile::sprite.push_back(std::make_shared<Sprite>("m8.png"));

  al_destroy_path(path);
}

__END_API