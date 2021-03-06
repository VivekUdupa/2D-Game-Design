#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "gameData.h"
#include "hud.h"
#include "smartSprite.h"

class Player;
class CollisionStrategy;

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();
  void switchSprite();

private:
  const Gamedata& gdata;
  //const RenderContext* rc;
  const RenderContext& rc;
  const IoMod& io;
  Clock& clock ;

  SDL_Renderer * const renderer;
  //Vector2f msgFPSPos;
  World greenSky;
  World greenClouds;
  World greenMountains;
  World greenBuildings;
  World greenBridge;
  World greenHouse;
  World greenGround;
  Viewport& viewport;

 std::vector<SmartSprite*> sprites;
 std::vector<CollisionStrategy*> strategies;
 int currentStrategy;
 int currentSprite;
 bool collision;
 
 // Drawable* ghost;
  Player* knightWalk;
  //TwoWayMultiSprite* zombieFall;

  SDL_Color colour;

  bool makeVideo;

  Hud& hud;

  void draw() const;
  void update(Uint32);

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
  void printScales() const;
  void checkForCollisions();
};
