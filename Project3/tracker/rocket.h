#ifndef ROCKET__H
#define ROCKET__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class Rocket : public Drawable {
public:
  Rocket(const std::string&);
  Rocket(const Rocket&);

  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual const Image* getImage() const { 
    return images[currentFrame]; 
  }
  int getScaledWidth()  const { 
    return getScale()*images[currentFrame]->getWidth(); 
  } 
  int getScaledHeight()  const { 
    return getScale()*images[currentFrame]->getHeight(); 
  } 
  virtual const SDL_Surface* getSurface() const { 
    return images[currentFrame]->getSurface();
  }

protected:
  std::vector<Image *> images;

  unsigned currentFrame;
  unsigned numberOfLeftFrames;
  unsigned numberOfRightFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;

  void advanceFrame(Uint32 ticks);
  Rocket& operator=(const Rocket&);
};
#endif
