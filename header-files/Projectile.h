#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "traits.h"
#include "configs.h"
#include "Drawable.h"
#include "Point.h"
#include "Vector.h"

__BEGIN_API

class Projectile
{
public:
	Projectile(Point point, ALLEGRO_COLOR color, Vector speed, bool isPlayerShot) : _point(point), _color(color), _speed(speed) {}
	virtual ~Projectile() {}

	virtual void draw() = 0;
	virtual void update(double dt) = 0;
	virtual int getSize() = 0;

	virtual int getDamage() = 0;
	virtual void ackHitSomething() = 0;
	virtual bool wasDestroyed() = 0;

	Point getPosition() { return _point; }
	bool getIsPlayerProjectile() { return _isPlayerShot; }
	bool isOutOfBounds()
	{
		if ((_point.x > Configs::_widthDisplay) ||
			(_point.x < 0) ||
			(_point.y > Configs::_heightDisplay) ||
			(_point.y < 0))
			return true;
		return false;
	}

protected:
	Point _point;
	ALLEGRO_COLOR _color;
	Vector _speed;
	bool _isPlayerShot;
};

__END_API

    #endif