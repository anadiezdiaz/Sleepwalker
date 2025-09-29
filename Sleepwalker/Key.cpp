#include "Key.h"

Key::Key(float x, float y, Game* game)
	: Actor("res/key.png", x, y, 22, 32, game) {

	moving = new Animation("res/key_animation.png", width, height, 256, 36, 6, 8, true, game);
	invisible = new Animation("", width, height, 256, 36, 6, 8, true, game);
	animation = moving;
}

void Key::draw(float scrollX)
{
	animation->draw(x - scrollX, y);
}

void Key::update()
{
	if (makeInvisible == true)
		animation = invisible;
	animation->update();
}
