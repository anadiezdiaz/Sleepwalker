#include "RecolectableLife.h"

RecolectableLife::RecolectableLife(float x, float y, Game* game)
	: Actor("res/vextra.png", x, y, 24, 20, game) {

	moving = new Animation("res/vidasextra.png", width, height, 197, 25, 6, 6, true, game);
	animation = moving;
}

void RecolectableLife::draw(float scrollX)
{
	animation->draw(x - scrollX, y);
}

void RecolectableLife::update()
{
	animation->update();
}
