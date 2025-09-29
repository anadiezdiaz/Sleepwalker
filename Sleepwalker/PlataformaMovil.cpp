#include "PlataformaMovil.h"

PlataformaMovil::PlataformaMovil(float x, float y, Game* game)
	: Actor("res/tileMovil.png", x, y, 45, 14, game) {

	vx = 1;
	vxIntelligence = -1;
	vx = vxIntelligence;
	animation = new Animation("res/tileMovil.png", width, height,
		45, 14, 6, 1, false, game);

}

void PlataformaMovil::draw(float scrollX) {
	animation->draw(x - scrollX, y);
}

void PlataformaMovil::update() {
	
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
	x = x + vx;

}

