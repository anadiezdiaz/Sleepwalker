#pragma once

#include "Actor.h"
#include "Animation.h"
class PlataformaMovil : public Actor
{
public:
	PlataformaMovil(float x, float y, Game* game);
	void draw(float scrollX);
	void update();
	float vxIntelligence;
	Animation* animation;
};

