#include "SpiderProjectile.h"

SpiderProjectile::SpiderProjectile(float x, float y, Game* game) :
	Actor("res/spider_shootizq.png", x, y, 45, 16, game) {
	vx = -4;
}

void SpiderProjectile::update() {
	x = x + vx;
}
