#include <cmath>
#include <random>
#include <functional>
#include "smartSprite.h"
#include "gameData.h"
#include "renderContext.h"

void SmartSprite::runLeft() {
	//setVelocityX( -fabs(getVelocityX()) );
	if( getX() > 0 ) {
		setVelocityX( -fabs(getVelocityX()) );		
	}
}

void SmartSprite::runRight() {
	//setVelocityX( fabs(getVelocityX()) );
	if( getX() < worldWidth - getScaledWidth() ) {
		setVelocityX( fabs(getVelocityX()) );		
	}
}

void SmartSprite::runUp() {
	//setVelocityY( -fabs(getVelocityY()) );
	if( getY() > 0 ) {
		setVelocityY( -fabs(getVelocityY()) );		
	}
}

void SmartSprite::runDown() {
	//setVelocityY( fabs(getVelocityY()) );
	if( getY() < worldHeight - getScaledHeight() ) {
		setVelocityY( fabs(getVelocityY()) );		
	}
}

float distance(float x1, float y1, float x2, float y2) {
	float x = x1 - x2;
	float y = y1 - y2;

	return hypot(x, y);
}

SmartSprite::SmartSprite(const std::string& name, const Vector2f& pos, int w, int h):
	TwoWayMultiSprite(name),
	playerPos(pos),
	playerWidth(w),
	playerHeight(h),
	currentMode(NORMAL),
	safeDistance(Gamedata::getInstance().getXmlFloat(name+"/safeDistance"))
	{}

SmartSprite::SmartSprite(const SmartSprite& s) :
	TwoWayMultiSprite(s),
	playerPos(s.playerPos),
	playerWidth(s.playerWidth),
	playerHeight(s.playerHeight),
	currentMode(s.currentMode),
	safeDistance(s.safeDistance)
	{}

void SmartSprite::update(Uint32 ticks) {
	TwoWayMultiSprite::update(ticks);
	float x = getX() + getImage()->getWidth()/2;
	float y = getY() + getImage()->getHeight()/2;
	float ex = playerPos[0] + playerWidth/2 + 75;
	float ey = playerPos[1] + playerHeight/2 + 75;
	float distanceToOpponent = ::distance(x, y, ex, ey);

	if(currentMode == NORMAL && distanceToOpponent < safeDistance) {
			currentMode = EVADE;
	}
	else if (currentMode == EVADE && distanceToOpponent > safeDistance) {
		currentMode = NORMAL;	
	}
	else if (currentMode == EVADE && distanceToOpponent < safeDistance) {
		if(x < ex) { runLeft(); }
		if(x > ex) { runRight(); }
		if(y < ey) { runUp(); }
		if(y > ey) { runDown(); }
	}

}
