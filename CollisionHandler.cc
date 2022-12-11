#include "header-files/CollisionHandler.h"

__BEGIN_API

void CollisionHandler::runCollision() {
  while (Configs::_isGameRunning) {
	checkCollision();
	removeObjects();
	Thread::yield();
  }
}

void CollisionHandler::checkCollision() {
  // Ship x Enemy
  for (auto listItem = _shipShots.begin(); listItem != _shipShots.end();) {
	Projectile *shipShot = *listItem;
	listItem++;

	// Checks if an enemy was hit
	for (auto enemyItem = _enemies.begin(); enemyItem != _enemies.end();) {
	  Enemy *enemy = *enemyItem;
	  enemyItem++;

	  if (checkHit(shipShot, enemy)) {
		enemy->hit(shipShot->getDamage());
		if (enemy->isDead()) {
		  _window->removeEnemy(enemy);
		  _enemies.remove(enemy);
		  delete enemy;
		}

		// Checks if ship shot hit something
		shipShot->ackHitSomething();

		// Checks if the shot was destroyed, if so remove it from window
		if (shipShot->wasDestroyed()) {
		  _window->removeProjectile(shipShot);
		  _shipShots.remove(shipShot);
		  delete shipShot;
		  break;
		}
	  }
	}
  }

  // Enemy x Ship
  for (auto listItem = _enemiesShots.begin(); listItem != _enemiesShots.end();) {
	Projectile *enemyShot = *listItem;
	listItem++;

	if (checkHit(enemyShot, _ship)) {
	  // Checks if an enemy hit something
	  enemyShot->ackHitSomething();

	  // Inflicts the damage to the player
	  _ship->hit(enemyShot->getDamage());

	  // Checks if the shot was destroyed, if so remove it from window
	  if (enemyShot->wasDestroyed()) {
		// Destrói o tiro
		_window->removeProjectile(enemyShot);
		_enemiesShots.remove(enemyShot);
		delete enemyShot;
	  }

	  if (_ship->isDead()) {
		Configs::_isGameRunning = false;
		return;
	  }
	}
  }

  // Checks if the enemy ship and the player ship collided
  for (auto listItem = _enemies.begin(); listItem != _enemies.end();) {
	Enemy *enemy = *listItem;
	listItem++;

	if (checkHit(enemy, _ship)) {
	  enemy->hit(1);

	  if (enemy->isDead()) {
		_window->removeEnemy(enemy);
		_enemies.remove(enemy);
		delete enemy;
	  }

	  _ship->hit(1);
	  if (_ship->isDead()) {
		Configs::_isGameRunning = false;
		return;
	  }
	}
  }
}

bool CollisionHandler::checkHit(Projectile *proj, Drawable *hitObj) {
  Point projPos = proj->getPosition();
  Point hitPos = hitObj->getPosition();
  int hitSize = hitObj->getSize();

  if (projPos.x > hitPos.x - hitSize &&
	  (projPos.x < hitPos.x + hitSize) &&
	  (projPos.y > hitPos.y - hitSize) &&
	  (projPos.y < hitPos.y + hitSize))
	return true;
  return false;
}

bool CollisionHandler::checkHit(Drawable *firstObj, Drawable *secondObj) {
  int firstSize = firstObj->getSize();
  int secondSize = secondObj->getSize();
  Point firstPos = firstObj->getPosition();
  Point secondPos = secondObj->getPosition();

  return (abs(firstPos.x - secondPos.x) < (firstSize + secondSize) &&
	  abs(firstPos.y - secondPos.y) < (firstSize + secondSize));
}

void CollisionHandler::removeObjects() {
  // Remove enemies
  for (auto enemyItem = _enemies.begin(); enemyItem != _enemies.end();) {
	Enemy *enemy = *enemyItem;
	enemyItem++;
	if (enemy->isOutOfBounds()) {
	  _window->removeEnemy(enemy);
	  _enemies.remove(enemy);
	  delete enemy;
	}
  }

  // Remove enemies shots
  for (auto enemyItem = _enemiesShots.begin(); enemyItem != _enemiesShots.end();) {
	Projectile *proj = *enemyItem;
	enemyItem++;
	if (proj->isOutOfBounds()) {
	  _window->removeProjectile(proj);
	  _enemiesShots.remove(proj);
	  delete proj;
	}
  }

  // Remove player shots
  for (auto shipShot = _shipShots.begin(); shipShot != _shipShots.end();) {
	Projectile *proj = *shipShot;
	shipShot++;
	if (proj->isOutOfBounds()) {
	  _window->removeProjectile(proj);
	  _shipShots.remove(proj);
	  delete proj;
	}
  }
}

void CollisionHandler::attachShip(Ship *ship) {
  _ship = ship;
}

void CollisionHandler::attachWindow(Window *window) {
  _window = window;
}

void CollisionHandler::newPlayerShot(Projectile *proj) {
  _shipShots.push_front(proj);
}

void CollisionHandler::newEnemyShot(Projectile *proj) {
  _enemiesShots.push_front(proj);
}

void CollisionHandler::newEnemyShip(Enemy *enemy) {
  _enemies.push_front(enemy);
}

void CollisionHandler::removeEnemyShip(Enemy *enemy) {
  _enemies.remove(enemy);
}

__END_API