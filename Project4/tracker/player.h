#ifndef PLAYER_H
#define PLAYER_H
#include<SDL.h>
#include<string>
#include<vector>
#include<cmath>

#include "drawable.h"

class Player : public Drawable {
public:
	Player(const std::string&);
	Player(const Player&);

	virtual void draw() const;
	virtual void update( Uint32 ticks );

	virtual const Image* getImage() const { return images[currentFrame]; }
	int getScaledWidth() const { return getScale()*images[currentFrame]->getWidth();  }
	int getScaledHeight() const { return getScale()*images[currentFrame]->getHeight();  }
	const SDL_Surface* getSurface() const { return images[currentFrame]->getSurface(); }

	void right();
	void left();
	void up();
	void down();
	void stop();

private:
	std::vector<Image *>images;

	unsigned currentFrame;
	unsigned numberOfRightFrames;
	unsigned numberOfLeftFrames;
	unsigned frameInterval;
	float timeSinceLastFrame;
	int worldWidth;
	int worldHeight;
	
	Vector2f initialVelocity;

	void advanceFrame(Uint32 ticks);
	Player& operator=(const Player&);

};
#endif
