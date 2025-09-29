#pragma once
#include "Actor.h"
#include "Animation.h"
class Dialog : public Actor
{
public:
	Dialog(float x, float y, Game* game);
	void mostrar();
	void update();
	void resetea();
	void draw(float scrollX);
	Animation* animation;
	Animation* dialog0;
	Animation* dialog1;
	Animation* dialog2;
	Animation* dialog3;
	Animation* dialog4;
	bool activadialog2;
	bool activadialog3;
	bool nodesactivesdialog2;
	bool eliminadas;
	
};





