#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	init();
}

void GameLayer::init() {
	space = new Space(1);
	scrollX = 0;
	tiles.clear();
	spiders.clear();
	recolectablesVida.clear();
	recolectablesTiempo.clear();
	powerUpGhosts.clear();
	tilesTemporales.clear();
	tilesMoviles.clear();
	tilesDestruibles.clear();
	cuerdas.clear();
	traps.clear();
	npcs.clear();
	ghosts.clear();
	spiderProjectiles.clear();
	audioBackground = Audio::createAudio("res/musica_ambiente.ogg", true);
	audioBackground->play();

	if (game->currentLevel == 0) {
		background = new Background("res/sotano.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);
	}
	else if (game->currentLevel == 1) {
		background = new Background("res/library.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);
	}
	else if (game->currentLevel == 2) {
		background = new Background("res/boss.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	}
	else {
		background = new Background("res/habitacion.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	}
	tiempoRestante = 500;
	textTiempoRestante = new Text("hola", WIDTH * 0.79, HEIGHT * 0.04, game);
	textTiempoRestante->content = to_string(tiempoRestante);

	etiquetaTiempo = new Text("Time left:  ", WIDTH * 0.64, HEIGHT * 0.04, game);

	vidasRestantes = new Text("5", WIDTH * 0.95, HEIGHT * 0.04, game);
	vidasDibujo = new Actor("res/vextra.png",
		WIDTH * 0.90, HEIGHT * 0.04, 24, 20, game);

	if (game->currentLevel == 3) {
		pause = true;
		message = new Actor("res/mensaje_ganar.png", WIDTH * 0.5, HEIGHT * 0.5,
			WIDTH, HEIGHT, game);
	}else {
		pause = true;
		message = new Actor("res/mensaje_como_jugar.png", WIDTH * 0.5, HEIGHT * 0.5,
			WIDTH, HEIGHT, game);
	}
	loadMap("res/" + to_string(game->currentLevel) + ".txt");
}

void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keysToControls(event);
	}
	//procesar controles
	// Eje X
	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}


	//en caso de coger el powerUp fantasma perdemos la gravedad y el movimiento en el eje y es libre
	if (player->isGhost == true) {
		if (controlMoveY > 0) {
			player->moveY(1);
		}
		else if (controlMoveY < 0) {
			player->moveY(-1);
		}
		else {
			player->moveY(0);
		}
	}
	//movimiento para trepar
	if (player->trepar == true) {
		if (controlMoveY > 0) {
			player->moveY(1);
		}
		else if (controlMoveY < 0) {
			player->moveY(-1);
		}
		else {
			player->moveY(0);
		}
	}

	// Eje Y
	if (controlMoveY > 0) {
	}
	else if (controlMoveY < 0) {
		player->jump();
	}
	else {
	}

	if (controlContinue) {
		pause = false;
		controlContinue = false;
	}



}

void GameLayer::update() {
	if (pause) {
		return;
	}

	// Jugador se cae
	if (player->y > HEIGHT + 80) {
		init();
	}
	if (player->y < -150) {
		init();
	}
	space->update();
	background->update();
	player->update();
	//comprobar si el tiempo se ha acabado
	delay--;
	if (delay == 0) {
		delay = 30;
		tiempoRestante--;
		textTiempoRestante->content = to_string(tiempoRestante);
	}
	if (tiempoRestante == 0) {
		init();
	}
	//comprobar overlap con key
	if (player->isOverlap(key)) {
		hasKey = true;
		space->removeDynamicActor(key);
		key->makeInvisible = true;
	}

	//comprobar si estas en la puerta con la llave
	if (player->isOverlap(door) && hasKey == true) {
		hasKey = false;
		space->removeDynamicActor(door);
		game->currentLevel++;
		if (game->currentLevel > game->finalLevel) {
			game->currentLevel = 0;
		}
		init();
	}

	//comprobamos colisiones con las cajas de vida 
	list<RecolectableLife*> deleteRecolectableVida;
	for (auto const& vida : recolectablesVida) {
		vida->update();
		if (player->isOverlap(vida)) {
			player->lifes++;
			vidasRestantes->content = to_string(player->lifes);
			deleteRecolectableVida.push_back(vida);
		}
	}
	for (auto const& deleteVida : deleteRecolectableVida) {
		space->removeDynamicActor(deleteVida);
		recolectablesVida.remove(deleteVida);
		delete deleteVida;
	}

	//comprobamos colisiones con las cajas de tiempo
	list<RecolectableTime*> deleteRecolectableTiempo;
	for (auto const& tiempo : recolectablesTiempo) {
		tiempo->update();
		if (player->isOverlap(tiempo)) {
			tiempoRestante = tiempoRestante + 100;
			textTiempoRestante->content = to_string(tiempoRestante);
			deleteRecolectableTiempo.push_back(tiempo);
		}
	}
	for (auto const& deleteTiempo : deleteRecolectableTiempo) {
		space->removeDynamicActor(deleteTiempo);
		recolectablesTiempo.remove(deleteTiempo);
		delete deleteTiempo;
	}

	//Tiles temporales
	list<Tile*> deleteTemporalTiles;
	for (auto const& temporalTile : tilesTemporales)
	{
		if (player->isOverlap(temporalTile))
		{
			temporalTile->temp--;
			if (temporalTile->temp == 0) {
				deleteTemporalTiles.push_back(temporalTile);
			}
		}
	}
	for (auto const& delTileTemp : deleteTemporalTiles)
	{
		space->removeStaticActor(delTileTemp);
		tilesTemporales.remove(delTileTemp);
	}
	deleteTemporalTiles.clear();


	//Tiles Moviles
	for (auto const& tileMovil : tilesMoviles) {
		tileMovil->update();
		for (auto const& tile : tiles) {
			if (tileMovil->isOverlap(tile)) {
				tileMovil->vx = 0;
			}
		}
	}

	//si colisionamos con un powerUpGhost se borra y se interacciona con el un determinado tiempo
	list<PowerUpGhost*> deletePowerUpGhosts;
	for (auto const& pg : powerUpGhosts) {
		pg->update();
		if (player->isOverlap(pg) && pg->visible == true) {
			for (auto const& ghost : ghosts) {
				ghost->visibles = true;
			}
			player->isGhost = true;
			space->gravity = 0;
			deletePowerUpGhosts.push_back(pg);
		}
		for (auto const& npc : npcs) {
			if (dialog->eliminadas == true && player->isOverlap(npc)) {
				pg->visible = true;
			}
		}
	}
	if (player->isGhost == true) {
		ghostTime--;
	}
	if (ghostTime == 0) {
		player->isGhost = false;
		for (auto const& ghost : ghosts) {
			ghost->visibles = false;
		}
		space->gravity = 1;
		ghostTime = 1000;
	}
	//comprobar colisiones con ghosts
	for (auto const& ghost : ghosts) {
		if (player->isOverlap(ghost) && ghost->visibles == true && player->isGhost == true) {
			delayghost--;
			if (delayghost <= 0) {
				delayghost = 50;
				tiempoRestante = tiempoRestante - 50;
				textTiempoRestante->content = to_string(tiempoRestante);
			}
		}
	}

	//actualizar key
	key->update();

	//arañas generan disparos solas
	list<Spider*>deleteSpiders;
	for (auto const& spider : spiders) {
		spider->update();
		if (spider->isInRender(scrollX) == true) {
			SpiderProjectile* enemyShoot = spider->autoshoot();
			if (enemyShoot != NULL) {
				spiderProjectiles.push_back(enemyShoot);
			}
		}
		if (player->isOverlap(spider) && player->hit == true)
			deleteSpiders.push_back(spider);
	}
	if (spiders.size() == 0)
		dialog->eliminadas = true;

	//si pegamos a un tileDestruible se elimina
	list<Tile*> deleteTilesDestruibles;
	for (auto const& tileDestruible : tilesDestruibles) {
		if (player->isOverlap(tileDestruible) && player->hit == true)
			deleteTilesDestruibles.push_back(tileDestruible);
	}
	for (auto const& deleteTileDestruible : deleteTilesDestruibles) {
		space->removeStaticActor(deleteTileDestruible);
		tilesDestruibles.remove(deleteTileDestruible);
		delete deleteTileDestruible;
	}
	//actualizar si no hay overlap con el NPC
	for (auto const& np : npcs) {
		if (player->isOverlap(np) == false) {
			activaunaopcion = false;
			dialog->resetea();

		}
		else {
			dialog->mostrar();
		}
	}
	//Colisiones player con spiderProjectiles
	list<SpiderProjectile*> deleteProjectilesCont;
	for (auto const& spiderProjectile : spiderProjectiles) {
		spiderProjectile->update();
		if (player->isOverlap(spiderProjectile)) {
			player->loseLife();
			vidasRestantes->content = to_string(player->lifes);
			deleteProjectilesCont.push_back(spiderProjectile);
		}
	}
	for (auto const& delProjectile : deleteProjectilesCont) {
		spiderProjectiles.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
	}
	deleteProjectilesCont.clear();

	for (auto const& ghost : ghosts) {
		ghost->update();
		if (player->isOverlap(ghost) && ghost->visibles == true) {
			player->isParalized = true;
			player->vx = 0;
			player->vy = 0;
		}
	}
	if (player->isParalized == true) {
		paralizedTime--;
	}
	if (paralizedTime == 0) {
		player->isParalized = false;
		paralizedTime = 20;
	}

	//comprobar si hay colision con una tile cuerda
	for (auto const& cuerda : cuerdas) {
		if (player->isOverlap(cuerda)) {
			player->trepar = true;
		}
		else {
			player->trepar = false;
		}

	}
	for (auto const& t : traps) {
		t->update();
		if (t->isOverlap(player)) {
			player->loseLife();
			vidasRestantes->content = to_string(player->lifes);
		}
	}

	for (auto const& pg : deletePowerUpGhosts) {
		space->removeStaticActor(pg);
		powerUpGhosts.remove(pg);
		delete pg;
	}

	for (auto const& spider : deleteSpiders) {
		space->removeDynamicActor(spider);
		spiders.remove(spider);
		delete spider;
	}
	dialog->update();
	for (auto const& g : tilesMoviles) {
		g->update();
	}

	if (player->lifes <= 0) {
		init();
	}

	cout << "update GameLayer" << endl;
}

void GameLayer::draw() {
	calculateScroll();
	background->draw(scrollX);
	for (auto const& tile : tiles) {
		tile->draw(scrollX);
	}
	for (auto const& tileTemporal : tilesTemporales) {
		tileTemporal->draw(scrollX);
	}
	for (auto const& cuerda : cuerdas) {
		cuerda->draw(scrollX);
	}
	for (auto const& tile : tilesMoviles) {
		tile->draw(scrollX);
	}
	for (auto const& tile : tilesDestruibles) {
		tile->draw(scrollX);
	}
	door->draw(scrollX);
	for (auto const& spiderP : spiderProjectiles) {
		spiderP->draw(scrollX);
	}
	for (auto const& spider : spiders) {
		spider->draw(scrollX);
	}
	key->draw(scrollX);
	for (auto const& pg : powerUpGhosts) {
		pg->draw(scrollX);
	}
	for (auto const& npc : npcs) {
		npc->draw(scrollX);
	}
	for (auto const& g : ghosts) {
		g->draw(scrollX);
	}
	for (auto const& g : traps) {
		g->draw(scrollX);
	}

	for (auto const& g : recolectablesTiempo) {
		g->draw(scrollX);
	}
	for (auto const& g : recolectablesVida) {
		g->draw(scrollX);
	}
	dialog->draw(scrollX);
	player->draw(scrollX);

	textTiempoRestante->draw();
	etiquetaTiempo->draw();
	vidasRestantes->draw();
	vidasDibujo->draw();
	if (pause) {
		message->draw();
	}

	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_QUIT) {
		game->loopActive = false;
	}
	if (event.type == SDL_KEYDOWN && player->isParalized == false) {
		controlContinue = true;
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_SPACE: // pega
			if (player->isGhost == false) {
				player->hit = true;
			}
			break;
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_0:
			game->scale();
			break;
		case SDLK_1:
			if (activaunaopcion == false)
				dialog->activadialog2 = true;
			activaunaopcion = true;
			dialog->nodesactivesdialog2 = true;
			break;
		case SDLK_2:
			if (activaunaopcion == false)
				dialog->activadialog3 = true;
			activaunaopcion = true;
			break;
		}

	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_SPACE: // pega
			if (player->isGhost == false) {
				player->hit = false;
			}
			break;
		}

	}

}


void GameLayer::loadMap(string name) {
	char character;
	string line;
	ifstream streamFile(name.c_str());
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Por línea
		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			mapWidth = line.length() * 40; // Ancho del mapa en pixels
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				cout << character;
				float x = 40 / 2 + j * 40; // x central
				float y = 32 + i * 32; // y suelo
				loadMapObject(character, x, y);
			}

			cout << character << endl;
		}
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case '1': {
		player = new Player(x, y, game);
		// modificación para empezar a contar desde el suelo.
		player->y = player->y - player->height / 2;
		space->addDynamicActor(player);
		break;
	}

	case 'L': {
		key = new Key(x, y, game);
		// modificación para empezar a contar desde el suelo.
		key->y = key->y - key->height / 2;
		space->addDynamicActor(key);
		break;
	}
	case '#': {
		Tile* tile = new Tile("res/tile.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'S': {
		Spider* spider = new Spider(x, y, game);
		// modificación para empezar a contar desde el suelo.
		spider->y = spider->y - spider->height / 2;
		spiders.push_back(spider);
		space->addDynamicActor(spider);
		break;
	}
	case 'P': {
		PowerUpGhost* pg = new PowerUpGhost(x, y, game);
		// modificación para empezar a contar desde el suelo.
		pg->y = pg->y - pg->height / 2;
		powerUpGhosts.push_back(pg);
		space->addDynamicActor(pg);
		break;
	}
	case 'N': {
		NPC* npc = new NPC(x, y, game);
		// modificación para empezar a contar desde el suelo.
		npc->y = npc->y - npc->height / 2;
		npcs.push_back(npc);
		space->addDynamicActor(npc);
		break;
	}

	case 'D': {
		dialog = new Dialog(x, y, game);
		// modificación para empezar a contar desde el suelo.
		dialog->y = dialog->y - dialog->height / 2;
		space->addDynamicActor(dialog);
		break;
	}
	case 'G': {
		Ghost* g = new Ghost(x, y, game);
		// modificación para empezar a contar desde el suelo.
		g->y = g->y - g->height / 2;
		ghosts.push_back(g);
		space->addDynamicActor(g);
		break;
	}
	case 'T': {
		Trap* g = new Trap(x, y, game);
		// modificación para empezar a contar desde el suelo.
		g->y = g->y - g->height / 2;
		traps.push_back(g);
		space->addDynamicActor(g);
		break;
	}case 'O': {
		door = new Door(x, y, game);
		// modificación para empezar a contar desde el suelo.
		door->y = door->y - door->height / 2;
		space->addDynamicActor(door);
		break;
	}
	case 'V': {
		RecolectableLife* recol = new RecolectableLife(x, y, game);
		// modificación para empezar a contar desde el suelo.
		recol->y = recol->y - recol->height / 2;
		recolectablesVida.push_back(recol);
		space->addDynamicActor(recol);
		break;
	}
	case 'M': {
		RecolectableTime* recol = new RecolectableTime(x, y, game);
		// modificación para empezar a contar desde el suelo.
		recol->y = recol->y - recol->height / 2;
		recolectablesTiempo.push_back(recol);
		space->addDynamicActor(recol);
		break;
	}
	case 'W': {
		Tile* tileTemporal = new Tile("res/tileTemporal.png", x, y, game);
		tileTemporal->y = tileTemporal->y - tileTemporal->height / 2;
		tilesTemporales.push_back(tileTemporal);
		space->addStaticActor(tileTemporal);
		break;
	}
	case 'A': {
		Tile* tileDestruible = new Tile("res/tileDestruible.png", x, y, game);
		tileDestruible->y = tileDestruible->y - tileDestruible->height / 2;
		tilesDestruibles.push_back(tileDestruible);
		space->addStaticActor(tileDestruible);
		break;
	}
	case 'C': {
		Cuerda* cuerda = new Cuerda("res/cuerda.png", x, y, game);
		cuerda->y = cuerda->y - cuerda->height / 2;
		cuerdas.push_back(cuerda);
		space->addDynamicActor(cuerda);
		break;
	}
	case 'I': {
		PlataformaMovil* tile = new PlataformaMovil(x, y, game);
		tile->y = tile->y - tile->height / 2;
		tilesMoviles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	}
}

void GameLayer::calculateScroll() {
	// limite izquierda
	if (player->x > WIDTH * 0.3) {
		if (player->x - scrollX < WIDTH * 0.3) {
			scrollX = player->x - WIDTH * 0.3;
		}
	}

	// limite derecha
	if (player->x < mapWidth - WIDTH * 0.3) {
		if (player->x - scrollX > WIDTH * 0.7) {
			scrollX = player->x - WIDTH * 0.7;
		}
	}
}





