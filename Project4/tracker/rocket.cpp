#include "rocket.h"
#include "gameData.h"
#include "imageFactory.h"

void Rocket::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
		if(getVelocityX() > 0)
    	{
			currentFrame = (currentFrame+1) % numberOfRightFrames;
		}
		else
		{
			currentFrame = numberOfRightFrames + (currentFrame+1) % numberOfLeftFrames;
		}
		timeSinceLastFrame = 0;
	}
}

Rocket::Rocket( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  //images( ImageFactory::getInstance()->getImages(name) ),
  images( ImageFactory::getInstance().getImages(name) ),

  currentFrame(0),
  numberOfLeftFrames( Gamedata::getInstance().getXmlInt(name+"/leftframes") ),
  numberOfRightFrames( Gamedata::getInstance().getXmlInt(name+"/rightframes") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

Rocket::Rocket(const Rocket& s) :
  Drawable(s), 
  images(s.images),
  currentFrame(s.currentFrame),
  numberOfLeftFrames( s.numberOfLeftFrames ),
  numberOfRightFrames( s.numberOfRightFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight )
  { }

Rocket& Rocket::operator=(const Rocket& s) {
  Drawable::operator=(s);
  images = (s.images);
  currentFrame = (s.currentFrame);
  numberOfLeftFrames = ( s.numberOfLeftFrames );
  numberOfRightFrames = ( s.numberOfRightFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  return *this;
}

void Rocket::draw() const { 
  images[currentFrame]->draw(getX(), getY(), getScale());
}

void Rocket::update(Uint32 ticks) { 
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
  }  

}
