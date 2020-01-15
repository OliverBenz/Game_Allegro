#ifndef PLAYER
#define PLAYER

#include "entity.hpp"
#include <vector>

class Player : public Entity {
public:
	Player(float fX, float fY, int iSizeW, int iSizeH);
	bool create();
	bool move(int winW, int winH);
};

#endif