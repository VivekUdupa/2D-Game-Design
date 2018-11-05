#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "gameData.h"

class Player;
class Hud;

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
  Vector2f msgFPSPos;
  World greenSky;
  World greenClouds;
  World greenMountains;
  World greenBuildings;
  World greenBridge;
  World greenHouse;
  World greenGround;
  Viewport& viewport;

  Drawable* star;
  Drawable* astronaut;
  Drawable* flyingSaucer;
  Player* knightWalk;
  int currentSprite;
  
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
