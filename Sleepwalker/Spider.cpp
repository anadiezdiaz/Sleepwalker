#include "Spider.h"
#include "SpiderProjectile.h"

Spider::Spider(float x, float y, Game* game)
	: Actor("res/spider.png", x, y, 50, 27, game) {

	state = game->stateMoving;

	aDying = new Animation("res/aranamuere.png", width, height,
		254, 36, 6, 6, false, game);

	aMoving = new Animation("res/spidersleft.png", width, height,
		465, 40, 6, 6, true, game);
	animation = aMoving;

	vx = 1;
	vxIntelligence = -1;
	vx = vxIntelligence;

}

void Spider::update() {
	// Actualizar la animación
	bool endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Estaba muriendo
		if (state == game->stateDying) {
			state = game->stateDead;
		}
	}


	if (state == game->stateMoving) {
		animation = aMoving;
	}
	if (state == game->stateDying) {
		animation = aDying;
	}

	// Establecer velocidad
	if (state != game->stateDying) {
		// no está muerto y se ha quedado parado
		if (vx == 0) {
			vxIntelligence = vxIntelligence * -1;
			vx = vxIntelligence;
		}
		if (outRight) {
			// mover hacia la izquierda vx tiene que ser negativa
			if (vxIntelligence > 0) {
				vxIntelligence = vxIntelligence * -1;
			}
			vx = vxIntelligence;
		}
		if (outLeft) {
			// mover hacia la derecha vx tiene que ser positiva
			if (vxIntelligence < 0) {
				vxIntelligence = vxIntelligence * -1;
			}
			vx = vxIntelligence;
		}

	}
	else {
		vx = 0;
	}

}

void Spider::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}
}


void Spider::draw(float scrollX) {
	animation->draw(x - scrollX, y);
}

SpiderProjectile* Spider::autoshoot() {
	if (spiderShootTime == 0) {
		spiderShootTime = spiderShootCadence;
		return new SpiderProjectile(x, y, game);
	}
	else {
		spiderShootTime--;
		return NULL;
	}
}

