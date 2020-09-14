#ifndef ENTITY
#define ENTITY

#include <allegro5/allegro.h>
#include <vector>

enum directions { UP, DOWN, LEFT, RIGHT };

class Entity {
protected:
	ALLEGRO_BITMAP* bm;
public:
	float x, y;
	int sizeW, sizeH;
	bool dir[4];

	Entity(float fX, float fY, int iSizeW, int iSizeH);
	virtual bool create(int r, int g, int b);
	virtual void draw();
	void destroy();
	virtual bool move(int winW, int winH) = 0;
};

#endif