#pragma once

#include "Actor.h"
#include "Animation.h"
#include "Audio.h"


class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	void update();
	void moveX(float axis);
	void moveY(float axis);
	//Audio* audioShoot;
	void draw(float scrollX = 0) override; // Va a sobrescribir
	void loseLife();
    Animation* animation; // Referencia a la animación mostrada

	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aRunningRight;
	Animation* aRunningLeft;

	Animation* aIdleRightGhost;
	Animation* aIdleLeftGhost;
	Animation* aRunningRightGhost;
	Animation* aRunningLeftGhost;
	Animation* aHitIzq;
	Animation* aHitDcha;

	int orientation;
	void jump();
	bool onAir;
	bool isGhost;
	bool trepar;
	bool hit;
	int lifes = 5;
	int invulnerableTime = 100;
	bool isParalized;

};



