#ifndef SMARTSPRITE_H
#define SMARTSPRITE_H

#include "twoWayMultiSprite.h"
#include <string.h>

class ExplodingSprite;

class SmartSprite : public TwoWayMultiSprite {
public:
	SmartSprite(const std::string&, const Vector2f& pos, int w, int h);
	SmartSprite(const SmartSprite&);
	SmartSprite& operator=(const SmartSprite&);	

	virtual void update(Uint32 ticks);
	void notify(const Vector2f& p) { playerPos = p;}

	bool killSprites() const { return spriteCollide;}
	virtual void collide();
	
private:
	enum MODE {NORMAL, EVADE};
	Vector2f playerPos;
	int playerWidth;
	int playerHeight;
	MODE currentMode;
	bool spriteCollide;
	float safeDistance;
	
	void runLeft();
	void runRight();
	void runUp();
	void runDown();
};
#endif
