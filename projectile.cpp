#include "projectile.hpp"

Projectile::Projectile(float fX, float fY, int iSizeW, int iSizeH, int iDamage) : Entity(fX, fY, iSizeW, iSizeH) {
	damage = iDamage;
}

bool Projectile::move(int winW, int winH) {
	y -= 4;
	if (y < 0 || y > winH || x < 0 || y > winW) {
		destroy();
		return false;
	}
	return true;
}