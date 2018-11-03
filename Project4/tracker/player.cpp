#include "player.h"
#include "gameData.h"

Player::Player( const std::string& name):
	player(name),
	initialVelocity(player.getVelocity()),
	worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
	worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
	{ }

void Player::stop() {
	player.setVelocityX(0);
	player.setVelocityY(0);
}

void Player::right() {
	if( player.getX() < worldWidth - getScaledWidth()) {
		player.setVelocityX(initialVelocity[0]);
	}
}

void Player::left() {
	if( player.getX() > 0 ) {
		player.setVelocityX( -initialVelocity[0] );
	}
}

void Player::down() {
	if ( player.getY() > worldWidth - getScaledWidth() ) {
		player.setVelocityY( initialVelocity[1]);
	}
}

void Player::up() {
	if( player.getY() < 0 ) {
		player.setVelocityY( - initialVelocity[1] );		
	}
}

void Player::update(Uint32 ticks) {
	player.update(ticks);
	stop();
}