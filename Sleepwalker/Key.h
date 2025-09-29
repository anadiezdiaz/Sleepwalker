#pragma once

#include "Actor.h"
#include "Animation.h"

class Key : public Actor
{
public:
	Key(float x, float y, Game* game);
	void draw(float scrollX);
	void update();
	Animation* moving;
	Animation* animation;
	Animation* invisible;
	bool makeInvisible;
};

