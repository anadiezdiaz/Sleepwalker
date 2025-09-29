#include "Trap.h"

Trap::Trap(float x, float y, Game* game)
	: Actor("res/trap.png", x, y, 60, 34, game) {

	animation = new Animation("res/traps.png", width, height,
		640, 90, 8, 4, true, game);

}

void Trap::update() {
	animation->update();
}

void Trap::draw(float scrollX) {
	animation->draw(x - scrollX, y);
}


