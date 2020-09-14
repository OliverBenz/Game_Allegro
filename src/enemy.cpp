#include "enemy.hpp"

Enemy::Enemy(float fX, float fY, int iSizeW, int iSizeH, int iHP) : Entity(fX, fY, iSizeW, iSizeH){
	hp = iHP;
}

bool Enemy::hit(int iDmg) {
	// Return -> isDead
	hp -= iDmg;
	if (hp <= 0)
		return true;
	return false;
}

bool Enemy::move(int winW, int winH) {
	return true;
}