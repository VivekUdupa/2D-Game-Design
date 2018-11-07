#ifndef SMARTSPRITE_H
#define SMARTSPRITE_H

#include <string.h>
#include "twoWayMultiSprite.h"

class SmartSprite : public TwoWayMultiSprite {
public:
	SmartSprite(const std::string&, const Vector2f& pos, int w, int h);
	SmartSPrite(const SmartSprite&);
	virtual ~SmartSprite() { }

	virtual void update(Uint32 ticks);
	void setPlayerPos(const Vector2f& p) { playerPos = p;}

private:
	enum MODE {NORMAL, EVADE};
	Vector2f playerPos;
	int playerWidth;
	int playerHeight;
	MODE currentMode;
	float safeDist;

	void runleft();
	void runRight();
	void runUp();
	void runDown();
};
#endif
