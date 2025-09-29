#pragma once

#include "Actor.h"
#include "Animation.h" 

class Ghost : public Actor
{
public:
	Ghost(float x, float y, Game* game);
	void draw(float scrollX = 0) override; // Va a sobrescribir
	void update();
	float vyIntelligence;
	Animation* aMoving;
	Animation* aInvisible;
	Animation* animation; // Referencia a la animación mostrada
	bool visibles;
};

