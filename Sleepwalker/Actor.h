#pragma once

#include "Game.h"

class Actor
{
public:
	Actor(string filename, float x, float y, int width, int height, Game* game);
	~Actor();
	virtual void draw(float scrollX = 0);
	bool isOverlap(Actor* actor);
	bool isOverlapDown(Actor* actor);
	bool isOverlapLeftRight(Actor* actor);
	bool isInRender(float scrollX);
	bool containsPoint(int pointX, int pointY);
	SDL_Texture* texture;
	int xP;
	int x;
	int y;
	float vx;
	float vxP;
	float vy;
	int width;
	int height;
	int fileWidth;
	int fileHeight;
	Game* game; // referencia al juego
	bool collisionDown;
	bool outRight;
	bool outLeft;
	bool outUp;
	bool outDown;

};



