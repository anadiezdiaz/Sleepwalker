#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/nimadcha.png", x, y, 50, 61, game) {
	
	aIdleRight = new Animation("res/nimadcha.png", width, height,
		420, 127, 10, 1, true, game);
	aIdleLeft = new Animation("res/nimaizq.png", width, height,
		420, 127, 10, 1, true, game);

	aRunningRight = new Animation("res/nimacaminadcha.png", width, height,
		450, 137, 10, 4, true, game);
	aRunningLeft = new Animation("res/nimacaminaizq.png", width, height,
		450, 137, 10, 4, true, game);


	aIdleRightGhost = new Animation("res/nimadchaghost.png", width, height,
		420, 146, 10, 1, true, game);
	aIdleLeftGhost = new Animation("res/nimaizqghost.png", width, height,
		420, 146, 10, 1, true, game);

	aRunningRightGhost = new Animation("res/nimacaminadchaghost.png", width, height,
		420, 146, 10, 4, true, game);
	aRunningLeftGhost = new Animation("res/nimacaminaizqghost.png", width, height,
		420, 146, 10, 4, true, game);

	aHitDcha = new Animation("res/ataque.png", width, height,
		450, 136, 10, 4, true, game);
	aHitIzq = new Animation("res/ataqueizq.png", width, height,
		450, 136, 10, 4, true, game);

	animation = aIdleRight;
	orientation = game->orientationRight;
	onAir = false;

}

void Player::jump() {
	if (!onAir) {
		vy = -16;
		onAir = true;
	}

}


void Player::update() {
	if (collisionDown == true) {
		onAir = false;
	}
	else {
		onAir = true;
	}

	animation->update();

	if (invulnerableTime > 0) {
		invulnerableTime--;
	}
	
	// Establecer orientación
	if (vx > 0) {
		orientation = game->orientationRight;
	}
	if (vx < 0) {
		orientation = game->orientationLeft;
	}

	// Selección de animación
	if(isGhost == false) {
		if (vx != 0) {
			if (orientation == game->orientationRight) {
				animation = aRunningRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aRunningLeft;
			}
		}

		if (vx == 0) {
			if (orientation == game->orientationRight) {
				animation = aIdleRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aIdleLeft;
			}
		}
	}else if(isGhost == true) {
		if (vx != 0) {
			if (orientation == game->orientationRight) {
				animation = aRunningRightGhost;
			}
			if (orientation == game->orientationLeft) {
				animation = aRunningLeftGhost;
			}
		}

		if (vx == 0) {
			if (orientation == game->orientationRight) {
				animation = aIdleRightGhost;
			}
			if (orientation == game->orientationLeft) {
				animation = aIdleLeftGhost;
			}
		}
	}
	if (hit == true) {
		if (orientation == game->orientationRight) {
			animation = aHitDcha;
		}
		if (orientation == game->orientationLeft) {
			animation = aHitIzq;
		}
	}
	
}

void Player::moveX(float axis) {
	if(isParalized == false)
		vx = axis * 3;
}

void Player::moveY(float axis) {
	if(isParalized == false)
		vy = axis * 3;
}


void Player::draw(float scrollX) {
	animation->draw(x - scrollX, y);
}

void Player::loseLife() {
	if (invulnerableTime <= 0) {
		if (lifes > 0) {
			lifes--;
			invulnerableTime = 100;
		}
	}
}





