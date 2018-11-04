#include "player.h"
#include "gameData.h"
#include "imageFactory.h"

Player::Player( const std::string& name):
	Drawable(name,
			Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
					 Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
			Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
					 Gamedata::getInstance().getXmlInt(name+"/speedY"))
			),
	images( ImageFactory::getInstance().getImages(name) ),
	
	currentFrame(0),
	numberOfRightFrames( Gamedata::getInstance().getXmlInt(name+"/leftframes") ),
	numberOfLeftFrames( Gamedata::getInstance().getXmlInt(name+"/rightframes") ),
	frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
	timeSinceLastFrame(0),
	worldWidth( Gamedata::getInstance().getXmlInt("world/width") ),
	worldHeight( Gamedata::getInstance().getXmlInt("world/height") ),
	initialVelocity( getVelocity() )
	{ }

Player::Player(const Player& s) :
	Drawable(s),
	images(s.images),
	currentFrame(s.currentFrame),
	numberOfRightFrames(s.numberOfRightFrames),
	numberOfLeftFrames(s.numberOfLeftFrames),
	frameInterval(s.frameInterval),
	timeSinceLastFrame(s.timeSinceLastFrame),
	worldWidth(s.worldWidth),
	worldHeight(s.worldHeight),
	initialVelocity(s.initialVelocity)
	{}

Player& Player::operator=(const Player& s) {
	Drawable::operator=(s);
	images = (s.images);
	currentFrame = (s.currentFrame);
	numberOfRightFrames = (s.numberOfRightFrames);
	numberOfLeftFrames = (s.numberOfLeftFrames);
	frameInterval = (s.frameInterval);
	timeSinceLastFrame = (s.timeSinceLastFrame);
	worldWidth = (s.worldWidth);
	worldHeight = (s.worldHeight);
	initialVelocity = (s.initialVelocity);
	return *this;
}

void Player::draw() const {
	images[currentFrame]-> draw(getX(), getY(), getScale());
}


void Player::stop() {
	setVelocityX(0);
	setVelocityY(0);
}

void Player::right() {
	if( getX() < worldWidth - getScaledWidth()) {
		setVelocityX(initialVelocity[0]);
	}
}

void Player::left() {
	if( getX() > 0 ) {
		setVelocityX( -initialVelocity[0] );
	}
}

void Player::down() {
	if ( getY() < worldHeight- getScaledHeight() ) {
		setVelocityY( initialVelocity[1]);
	}
}

void Player::up() {
	if( getY() > 0 ) {
		setVelocityY( -initialVelocity[1] );		
	}
}

void Player::update(Uint32 ticks) {
	//player.update(ticks);
	//stop();
	advanceFrame(ticks);

	Vector2f incr = getVelocity() * static_cast<float>(ticks) *  0.001;
	setPosition(getPosition() + incr); 

	if( getY() < 0 ) {
		setVelocityY( -fabs(getVelocityY()) );
	}

	if( getY() > worldHeight - getScaledHeight() ) {
		setVelocityY( fabs(getVelocityY()) );
	} 

	if( getX() < 0 ) {
		setVelocityX( -fabs(getVelocityX()) );
	}

	if( getX() > worldWidth - getScaledWidth() ) {
		setVelocityX( fabs(getVelocityX()) );
	} 
	
	stop();
}

void Player::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
		if(getVelocityX() >= 0)
    	{
			currentFrame = (currentFrame+1) % numberOfLeftFrames;
		}
		else
		{
			currentFrame = numberOfLeftFrames + (currentFrame+1) % numberOfRightFrames;
		}
		timeSinceLastFrame = 0;
	}

}
