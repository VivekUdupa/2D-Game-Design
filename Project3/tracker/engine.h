#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "gameData.h"

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
  World world;
  World planetsBig;
  World planetsSmall;
  Viewport& viewport;

  Drawable* star;
  Drawable* astronaut;
  Drawable* flyingSaucer;
  Drawable* rocket;
  int currentSprite;
  
  SDL_Color colour;

  bool makeVideo;

  void draw() const;
  void update(Uint32);

  Engine(const Engine&);
  Engine& operator=(const Engine&);
  void printScales() const;
  void checkForCollisions();
};
