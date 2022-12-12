#include "header-files/CollisionHandler.h"

__BEGIN_API

void CollisionHandler::runCollision() {
  while (Configs::_isGameRunning) {
	checkCollidingEnemyWithPlayer();
	checkCollisionOnEnemies();
	checkCollisionOnPlayer();
	clearEnemies();
	clearProjectiles();
	Thread::yield();
  }
}

void CollisionHandler::checkCollisionOnEnemies()
{
  // Ship x Enemy
  for (auto listItem = _shipShots.begin(); listItem != _shipShots.end();) {
	Projectile *shipShot = *listItem;
	listItem++;

	// Checks if an enemy was hit
	for (auto enemyItem = _enemies.begin(); enemyItem != _enemies.end();) {
	  Enemy *enemy = *enemyItem;
	  enemyItem++;
	  if (checkHit(shipShot, enemy))
	  	break;
	}
  }
}

void CollisionHandler::checkCollidingEnemyWithPlayer()
{
  // Checks if the enemy ship and the player ship collided
  for (auto listItem = _enemies.begin(); listItem != _enemies.end();) {
	Enemy *enemy = *listItem;
	listItem++;
	checkHit(enemy, _ship);
  }
}

void CollisionHandler::checkCollisionOnPlayer() {
  // Enemy x Ship
  for (auto listItem = _enemiesShots.begin(); listItem != _enemiesShots.end();) {
	Projectile *enemyShot = *listItem;
	listItem++;
	checkHit(enemyShot, _ship);
  }
}

// Checks Player shot -> Enemy Ship
bool CollisionHandler::checkHit(Projectile *proj, Enemy *target) {
  Point projPos = proj->getPosition();
  Point targetPos = target->getPosition();
  int targetSize = target->getSize();

  if (projPos.x > targetPos.x - targetSize &&
	  (projPos.x < targetPos.x + targetSize) &&
	  (projPos.y > targetPos.y - targetSize) &&
	  (projPos.y < targetPos.y + targetSize))
	{
		target->hit(proj->getDamage());
		if (target->getDead()) {
			_window->removeEnemy(target);
			_enemies.remove(target);
			delete target;
		}

		// Notifies the ship that the shot hit something
		proj->ackHitSomething();

		// Checks if the shot was destroyed, if so remove it from window
		if (proj->wasDestroyed()) {
		  _window->removeProjectile(proj);
		  _shipShots.remove(proj);
		  delete proj;
		  return true;
		}
	 }
	return false;
}

// Checks Enemy shot -> Player Ship
void CollisionHandler::checkHit(Projectile *proj, Ship *target) {
  Point projPos = proj->getPosition();
  Point targetPos = target->getPosition();
  int targetSize = target->getSize();

  if (projPos.x > targetPos.x - targetSize &&
	  (projPos.x < targetPos.x + targetSize) &&
	  (projPos.y > targetPos.y - targetSize) &&
	  (projPos.y < targetPos.y + targetSize))
	{
	  // Notifies the enemy that he hit something
	  proj->ackHitSomething();

	  // Inflicts the damage to the player
	  _ship->hit(proj->getDamage());

	  // Checks if the shot was destroyed, if so remove it from window
	  if (proj->wasDestroyed()) {
		_window->removeProjectile(proj);
		_enemiesShots.remove(proj);
		delete proj;
	  }

	  if (_ship->getDead())
		Configs::_isGameRunning = false;
	}
}

// Checks if Player ship collides Enemy Ship
void CollisionHandler::checkHit(Drawable *firstObj, Drawable *secondObj) {
  int firstSize = firstObj->getSize();
  int secondSize = secondObj->getSize();
  Point firstPos = firstObj->getPosition();
  Point secondPos = secondObj->getPosition();

	if( abs(firstPos.x - secondPos.x) < (firstSize + secondSize) &&
		abs(firstPos.y - secondPos.y) < (firstSize + secondSize)) {
		
		firstObj->hit(1);
		if (firstObj->getDead()) {
			_window->removeEnemy((Enemy *) firstObj);
			_enemies.remove((Enemy *) firstObj);
			delete firstObj;
		}

		_ship->hit(1);
		if (_ship->getDead())
			Configs::_isGameRunning = false;
	}
}

void CollisionHandler::clearEnemies() {
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
}

void CollisionHandler::clearProjectiles() {
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

void CollisionHandler::clearMines() {
	// Remove mines
  	for (auto mines = _mines.begin(); mines != _mines.end();) {
	Mine *mine = *mines;
	mines++;
	if (mine->isOutOfBounds()) {
	  _window->removeEnemy(mine);
	  delete mine;
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

void CollisionHandler::newMine(Mine *mine) {
	_mines.push_front(mine);
}

void CollisionHandler::removeMine(Mine *mine) {
	_mines.remove(mine);
}

__END_API