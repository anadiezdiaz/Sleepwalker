#pragma once

#include "Actor.h"
#include "Animation.h"

class RecolectableTime : public Actor
{
public:
	RecolectableTime(float x, float y, Game* game);
	void draw(float scrollX);
	void update();
	Animation* moving;
	Animation* animation;
};