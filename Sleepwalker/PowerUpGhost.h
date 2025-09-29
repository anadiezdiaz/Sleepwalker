#pragma once

#include "Actor.h"
#include "Animation.h"

class PowerUpGhost : public Actor
{
public:
	PowerUpGhost(float x, float y, Game* game);
	void draw(float scrollX);
	void update();
	Animation* moving;
	Animation* animation;
	Animation* invisible;
	bool visible;
};

