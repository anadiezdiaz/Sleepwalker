#pragma once

#include "Actor.h"

class SpiderProjectile : public Actor
{
public:
	SpiderProjectile(float x, float y, Game* game);
	void update();
};

