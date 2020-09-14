#include "player.hpp"
#include "entity.hpp"

Player::Player(float fX, float fY, int iSizeW, int iSizeH) : Entity(fX, fY, iSizeW, iSizeH) {}

bool Player::move(int winW, int winH) {
	if (dir[UP] && y >= 4.0) {
		y -= 4.0;
	}

	if (dir[DOWN] && y <= winH - sizeH - 4) {
		y += 4.0;
	}

	if (dir[LEFT] && x >= 4.0) {
		x -= 4.0;
	}

	if (dir[RIGHT] && x <= winW - sizeW - 4) {
		x += 4.0;
	}
	return true;
}

bool Player::create() {
	bm = al_load_bitmap("resources/player.png");
	return bm == NULL ? false : true;
}
