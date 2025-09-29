#include "Dialog.h"
#include "Actor.h"

Dialog::Dialog(float x, float y, Game* game):
	Actor("res/1.png", x, y, 100, 100, game) {

	dialog0 = new Animation("", width, height,
		100, 100, 5, 1, true, game);
	dialog1 = new Animation("res/1.png", width, height,
		100, 100, 5, 1, true, game);
	dialog2 = new Animation("res/2.png", width, height,
		100, 100, 5, 1, true, game);
	dialog3 = new Animation("res/3.png", width, height,
		100, 100, 5, 1, true, game);
	dialog4 = new Animation("res/4.png", width, height,
		100, 100, 5, 1, true, game);

	animation = dialog0;
	eliminadas = false;

	
}

void Dialog::mostrar()
{
	if(eliminadas == false && nodesactivesdialog2 == false) {
		animation = dialog1;
	}else if (eliminadas == false && nodesactivesdialog2 == true) {
		animation = dialog2;
	}
	else {
		animation = dialog4;
	}
}

void Dialog::update()

{
		if(activadialog2 == true) {
			animation = dialog2;
		}
		if (activadialog3 == true) {
			animation = dialog3;
		}
		animation->update();
	


	
}

void Dialog::resetea()
{
	activadialog2 = false;
	activadialog3 = false;
	animation = dialog0;

}

void Dialog::draw(float scrollX) {
	animation->draw(x - scrollX, y);
}




