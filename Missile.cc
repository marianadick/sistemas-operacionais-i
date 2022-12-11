#include <allegro5/allegro_primitives.h>
#include "header-files/Missile.h"

__BEGIN_API

std::vector<std::shared_ptr<Sprite>> Missile::sprites;
int Missile::SPRITES_VECTOR_MAX_INDEX = 7;
int Missile::DAMAGE = 2;

Missile::Missile(Point point, ALLEGRO_COLOR color, Vector speed, bool isPlayerShot) : Projectile(point,
																								 color,
																								 speed,
																								 isPlayerShot) {
  this->loadSprites();

  if (isPlayerShot) // Corrige o sprite de míssil
	this->angle = (atan(speed.y / speed.x) + 4.71) * -1;
  else
	this->angle = atan(speed.y / speed.x) + 4.71;

  // Move um pouco para frente da nave
  this->_point = this->_point + this->_speed * 0.1;
}

Missile::~Missile() {}

void Missile::draw() {
  Missile::sprites[currentSpriteIndex]->draw_rotated(this->_point, this->angle, 0);
  currentSpriteIndex++;
  if (currentSpriteIndex > Missile::SPRITES_VECTOR_MAX_INDEX)
	currentSpriteIndex = 0; // Reset o index para acessar o vetor de sprites
}

void Missile::update(double diffTime) {
  this->_point = this->_point + this->_speed * diffTime;
}

void Missile::ackHitSomething() {}

bool Missile::wasDestroyed() { return false; }

int Missile::getDamage() { return Missile::DAMAGE; }

int Missile::getSize() { return 3; }

void Missile::loadSprites() {
  ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
  al_append_path_component(path, "resources");
  al_change_directory(al_path_cstr(path, '/'));

  Missile::sprites.push_back(std::make_shared<Sprite>("m1.png"));
  Missile::sprites.push_back(std::make_shared<Sprite>("m2.png"));
  Missile::sprites.push_back(std::make_shared<Sprite>("m3.png"));
  Missile::sprites.push_back(std::make_shared<Sprite>("m4.png"));
  Missile::sprites.push_back(std::make_shared<Sprite>("m5.png"));
  Missile::sprites.push_back(std::make_shared<Sprite>("m6.png"));
  Missile::sprites.push_back(std::make_shared<Sprite>("m7.png"));
  Missile::sprites.push_back(std::make_shared<Sprite>("m8.png"));

  al_destroy_path(path);
}

__END_API