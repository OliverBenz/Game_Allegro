#include "entity.hpp"

Entity::Entity(float fX, float fY, int iSizeW, int iSizeH) {
	x = fX;
	y = fY;
	sizeW = iSizeW;
	sizeH = iSizeH;
	bm = NULL;

	// Direction
	dir[UP] = false;
	dir[DOWN] = false;
	dir[LEFT] = false;
	dir[RIGHT] = false;
}

bool Entity::create(int r, int g, int b) {
	bm = al_create_bitmap(sizeW, sizeH);
	
	if (!bm)
		return false;
	else {
		al_set_target_bitmap(bm);
		al_clear_to_color(al_map_rgb(r, g, b));
		return true;
	}
}

void Entity::draw() {
	al_draw_bitmap(bm, x, y, 0);
}

void Entity::destroy() {
	al_destroy_bitmap(bm);
}