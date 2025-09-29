#include "Ghost.h"

Ghost::Ghost(float x, float y, Game* game)
	: Actor("res/ghost.png", x, y, 32, 32, game) {
	aInvisible = new Animation("", width, height,
		128, 32, 6, 4, true, game);
	aMoving = new Animation("res/ghosts.png", width, height,
		128, 32, 6, 4, true, game);
	animation = aInvisible;
	vy = 1;
	vyIntelligence = -1;
	vy = vyIntelligence;

}

void Ghost::update() {
	if (visibles == true) {
		animation = aMoving;
	}else {
		animation = aInvisible;
	}
		// se ha quedado parado
		if (vy == 0) {
			vyIntelligence = vyIntelligence * -1;
			vy = vyIntelligence;
		}
		if (outUp) {
			// mover hacia la izquierda vy tiene que ser negativa
			if (vyIntelligence > 0) {
				vyIntelligence = vyIntelligence * -1;
			}
			vy = vyIntelligence;
		}
		if (outDown) {
			// mover hacia la derecha vy tiene que ser positiva
			if (vyIntelligence < 0) {
				vyIntelligence = vyIntelligence * -1;
			}
			vy = vyIntelligence;
		}
		animation->update();
	

}

void Ghost::draw(float scrollX) {
	animation->draw(x - scrollX, y);
}

