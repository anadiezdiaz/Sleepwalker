#pragma once

#include "Actor.h"
#include "Animation.h"

class RecolectableLife : public Actor
{
public:
	RecolectableLife(float x, float y, Game* game);
	void draw(float scrollX);
	void update();
	Animation* moving;
	Animation* animation;
};
