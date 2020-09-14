#ifndef ENEMY
#define ENEMY

#include "entity.hpp"

class Enemy : public Entity {
private:
	int hp;

public:
	Enemy(float fX, float fY, int iSizeW, int iSizeH, int iHP);
	bool hit(int iDmg);
	bool move(int winW, int winH);
};

#endif