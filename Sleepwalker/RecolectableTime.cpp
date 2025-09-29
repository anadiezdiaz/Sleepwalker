#include "RecolectableTime.h"

RecolectableTime::RecolectableTime(float x, float y, Game* game)
	: Actor("res/cajatiempo.png", x, y, 27, 27, game) {

	moving = new Animation("res/cajastiempo.png", width, height, 452, 52, 6, 7, true, game);
	animation = moving;
}

void RecolectableTime::draw(float scrollX)
{
	animation->draw(x - scrollX, y);
}

void RecolectableTime::update()
{
	animation->update();
}
