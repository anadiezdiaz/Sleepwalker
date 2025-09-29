#pragma once

#include "Actor.h"
#include "Animation.h" 
#include "SpiderProjectile.h"

class Spider : public Actor
{
public:
	Spider(float x, float y, Game* game);
	void draw(float scrollX = 0) override; // Va a sobrescribir
	void update();
	void impacted(); // Recibe impacto y pone animación de morir
	SpiderProjectile* autoshoot();
	float vxIntelligence;
	int state;
	Animation* aDying;
	Animation* aMoving;
	Animation* animation; // Referencia a la animación mostrada
	int spiderShootTime = 0;
	int spiderShootCadence = 100;
};

