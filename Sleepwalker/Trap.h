#pragma once

#include "Actor.h"
#include "Animation.h" 

class Trap : public Actor
{
public:
	Trap(float x, float y, Game* game);
	void draw(float scrollX = 0) override; // Va a sobrescribir
	void update();
	Animation* animation; // Referencia a la animación mostrada
};