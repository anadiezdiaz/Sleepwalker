#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Audio.h"
#include "Animation.h"
#include "Tile.h"
#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include <list>
#include "Space.h" // importar
#include "Spider.h"
#include "Key.h"
#include "SpiderProjectile.h"
#include "PowerUpGhost.h"
#include "Text.h"
#include "NPC.h"
#include "Dialog.h"
#include "PlataformaMovil.h"
#include "Ghost.h"
#include "Door.h"
#include "Trap.h"
#include "RecolectableLife.h"
#include "RecolectableTime.h"
#include "Cuerda.h"


class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	int mapWidth;
	Actor* message;
	bool pause;
	bool controlContinue = false;
	list<Tile*> tiles;
	list<Tile*> tilesTemporales;
	list<Cuerda*> cuerdas;
	list<Tile*> tilesDestruibles;
	list<PlataformaMovil*> tilesMoviles;
	void calculateScroll();
	float scrollX;
	Space* space;
	Player* player;
	Spider* spider;
	list<Spider*> spiders;
	Background* background;
	Audio* audioBackground;
	list<NPC*> npcs;
	bool controlHit = false;
	int controlMoveY = 0;
	int controlMoveX = 0;
	list<SpiderProjectile*> spiderProjectiles;
	list<PowerUpGhost*> powerUpGhosts;
	int tilesTemp = 20;
	int ghostTime = 1000;
	int paralizedTime = 20;
	Key* key;
	bool hasKey;
	Dialog* dialog;
	bool activaunaopcion = false;
	list<Ghost*> ghosts;
	list<Trap*> traps;
	Door* door;
	list<RecolectableLife*> recolectablesVida;
	list<RecolectableTime*> recolectablesTiempo;
	int tiempoRestante;
	Text* textTiempoRestante;
	int delay = 30;
	Text* etiquetaTiempo;
	Text* vidasRestantes;
	int delayghost;
	Actor* vidasDibujo;
};





