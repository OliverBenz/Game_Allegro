#ifndef PROJECTILE
#define PROJECTILE

#include "entity.hpp"

class Projectile : public Entity {
public:
	int damage;

	Projectile(float fX, float fY, int iSizeW, int iSizeH, int iDamage);
	bool move(int winW, int winH);
};

#endif