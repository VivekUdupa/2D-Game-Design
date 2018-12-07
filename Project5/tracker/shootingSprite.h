#include <string>
#include <iostream>
#include "player.h"
#include "bulletPool.h"

class ShootingSprite : public Player{
public:
  ShootingSprite(const std::string& n);
  ShootingSprite(const ShootingSprite& s);

  virtual void update(Uint32 ticks);
  virtual void draw() const;
  void shoot();
  virtual bool collidedWith(const Drawable*) const;
  std::list<Bullet> getBulletList();
  bool shooting();

private:
  std::string bulletName;
  BulletPool bullets;
  float minSpeed;
  int worldWidth;
  int worldHeight;
  ShootingSprite& operator=(const ShootingSprite&);
};
