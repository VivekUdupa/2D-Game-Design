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
	observers(std::list<SmartSprite*> {}),
	images( ImageFactory::getInstance().getImages(name) ),
	
	currentFrame(0),
	numberOfRightFrames( Gamedata::getInstance().getXmlInt(name+"/leftframes") ),
	numberOfLeftFrames( Gamedata::getInstance().getXmlInt(name+"/rightframes") ),
	frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
	timeSinceLastFrame(0),
	worldWidth( Gamedata::getInstance().getXmlInt("world/width") ),
	worldHeight( Gamedata::getInstance().getXmlInt("world/height") ),
	collision(false),
	initialVelocity( getVelocity() )
	{ }

Player::Player(const Player& s) :
	Drawable(s),
	observers(std::list<SmartSprite*> {}),
	images(s.images),
	currentFrame(s.currentFrame),
	numberOfRightFrames(s.numberOfRightFrames),
	numberOfLeftFrames(s.numberOfLeftFrames),
	frameInterval(s.frameInterval),
	timeSinceLastFrame(s.timeSinceLastFrame),
	worldWidth(s.worldWidth),
	worldHeight(s.worldHeight),
	collision(s.collision),
	initialVelocity(s.initialVelocity)
	{}

Player& Player::operator=(const Player& s) {
	Drawable::operator=(s);
	observers = s.observers;
	images = (s.images);
	currentFrame = (s.currentFrame);
	numberOfRightFrames = (s.numberOfRightFrames);
	numberOfLeftFrames = (s.numberOfLeftFrames);
	frameInterval = (s.frameInterval);
	timeSinceLastFrame = (s.timeSinceLastFrame);
	worldWidth = (s.worldWidth);
	worldHeight = (s.worldHeight);
	collision = s.collision;
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
		currentFrame = (currentFrame) % numberOfRightFrames;
	}
}

void Player::left() {
	if( getX() > 0 ) {
		setVelocityX( -initialVelocity[0] );
		currentFrame = numberOfRightFrames + (currentFrame) % numberOfLeftFrames;
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
	
	std::list<SmartSprite*>::iterator o = observers.begin();
	while( o != observers.end() ) {
		(*o)->notify( getPosition() );
		++o;
	}
	
	if(!collision) {
		advanceFrame(ticks);
	}

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
		//To advance Frames towards Right
		if(getVelocityX() > 0)
    	{
			currentFrame = (currentFrame+1) % numberOfRightFrames;
		}
		//To keep the player idle
		else if(getVelocityX() == 0)
		{
			currentFrame = currentFrame;
		}
		//To advance Frames towards Left 
		else
		{
			currentFrame = numberOfRightFrames + (currentFrame+1) % numberOfLeftFrames;
		}

		timeSinceLastFrame = 0;
	}

}

void Player::detach (SmartSprite* o) {
	std::list<SmartSprite*>::iterator sp = observers.begin();
	while (sp != observers.end()) {
		if(*sp == o) {
			sp = observers.erase(sp);
			return;
		}
		++sp;
	}
}
