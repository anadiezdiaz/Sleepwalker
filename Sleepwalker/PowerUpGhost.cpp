#include "PowerUpGhost.h"

PowerUpGhost::PowerUpGhost(float x, float y, Game* game)
	: Actor("res/powerUpGhost1.png", x, y, 40, 40, game) {
	invisible = new Animation("", width, height, 300, 64, 6, 5, true, game);
	moving = new Animation("res/powerUpGhost.png", width, height, 300, 64, 6, 5, true, game);
	animation = invisible;
}

void PowerUpGhost::draw(float scrollX)
{
	animation->draw(x - scrollX, y);
}

void PowerUpGhost::update()
{
	if (visible == true)
		animation = moving;
	animation->update();
}
