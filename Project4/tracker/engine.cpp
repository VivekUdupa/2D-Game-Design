#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "twoWayMultiSprite.h"
#include "gameData.h"
#include "engine.h"
#include "frameGenerator.h"
#include "player.h"
#include "hud.h"
#include "collisionStrategy.h"


Engine::~Engine() { 
  for (auto sprite : sprites) {
  	delete sprite;
  }
  
  for (CollisionStrategy* strategy : strategies) {
  	delete strategy;
  }

  delete knightWalk;
  
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  gdata(Gamedata::getInstance()),
  rc( RenderContext::getInstance() ),
  io( IoMod::getInstance() ),
  clock( Clock::getInstance() ),
  //renderer( rc->getRenderer() ),
  renderer( rc.getRenderer() ),
  //FPS
  //msgFPSPos(
  //  Vector2f( gdata.getXmlInt("viewFPS/loc/x"), gdata.getXmlInt("viewFPS/loc/y") )
  //),
  greenSky("greenSky", Gamedata::getInstance().getXmlInt("greenSky/factor") ),
  greenClouds("greenClouds", Gamedata::getInstance().getXmlInt("greenClouds/factor") ),
  greenMountains("greenMountains", Gamedata::getInstance().getXmlInt("greenMountains/factor") ),
  greenBuildings("greenBuildings", Gamedata::getInstance().getXmlInt("greenBuildings/factor") ),
  greenBridge("greenBridge", Gamedata::getInstance().getXmlInt("greenBridge/factor") ),
  greenHouse("greenHouse", Gamedata::getInstance().getXmlInt("greenHouse/factor") ),
  greenGround("greenGround", Gamedata::getInstance().getXmlInt("greenGround/factor") ),
  viewport( Viewport::getInstance() ),
  sprites(std::vector<SmartSprite*> {}),
  strategies(std::vector<CollisionStrategy*> {}),
  currentStrategy(0),
  currentSprite(0),
  collision(false),
  //ghost(new TwoWayMultiSprite("ghost")),
  knightWalk(new Player("knightWalk")),
  //zombieFall(new TwoWayMultiSprite("zombieFall")),
  colour({0, 0, 0xff, 0}),
  makeVideo( false ),
  hud(Hud::getInstance())
{
  //ghost->setScale(0.15);  
  knightWalk->setScale(0.15); 
	
  int n = gdata.getXmlInt("ghost/count");
  Vector2f pos = knightWalk->getPosition();
  int w = knightWalk->getScaledWidth();
  int h = knightWalk->getScaledHeight();
  sprites.reserve(n);

  std::cout << "count: " << n << " width = " << w << " height = " << h << std::endl;

  for (int i = 0; i < n; ++i) {
  	sprites.push_back(new SmartSprite("ghost", pos, w, h) );
    knightWalk->attach(sprites[i]);
  }

  //knightWalk->attach(sprites[0]);

  strategies.push_back( new RectangularCollisionStrategy );
  strategies.push_back( new PerPixelCollisionStrategy );
  strategies.push_back( new MidPointCollisionStrategy );


  Viewport::getInstance().setObjectToTrack(knightWalk);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
 //Background
 greenSky.draw();
 greenClouds.draw();
 greenMountains.draw();
 greenBuildings.draw();
 greenBridge.draw();
 greenHouse.draw();
 greenGround.draw();

 std::stringstream strm;
 strm << "Ghosts Remaining: " << sprites.size() << std::endl;
 io.writeText(strm.str(), 30, 60);

  for (const Drawable* sprite : sprites) {
  	sprite->draw();
  }
	
  strategies[currentStrategy]->draw();
  if(collision){
  	IoMod::getInstance().writeText("Oops Collision!!", 500, 100);
  }

  knightWalk->draw();
  //zombieFall->draw();
  
  hud.draw();

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  checkForCollisions();

  knightWalk->update(ticks);
  //zombieFall->update(ticks);

  for (Drawable* sprite : sprites) {
  	sprite->update(ticks);
  }

  greenSky.update();
  greenClouds.update();
  greenMountains.update();
  greenBuildings.update();
  greenBridge.update();
  greenHouse.update();
  greenGround.update();
 
  viewport.update(); // always update viewport last
}

/*
void Engine::checkForCollisions() {
	collision = false;
	for (const Drawable* c : sprites) {
		if( strategies[currentStrategy]->execute(*knightWalk, *c) ) {
			collision = true;
		}
	}

	if(collision) {
		knightWalk->collided();
	}
	else {
		knightWalk->missed();
		collision = false;
	}
}
*/

void Engine::checkForCollisions() {
	collision = false;
	auto it = sprites.begin();
	while( it != sprites.end() ) {
		if( strategies[currentStrategy]->execute(*knightWalk, **it) ) {
		collision = true;
		knightWalk->collided();
		SmartSprite* doa = *it;
		knightWalk->detach(doa);
		delete doa;
		it = sprites.erase(it);
		}
	else{
	++it;
	knightWalk->missed();
	collision = false;
	} 
	}
}

void Engine::switchSprite() {
	++currentSprite;
	currentSprite = currentSprite % (sprites.size() + 1) ; //+1 for the player
//	std::cout << "currentSprite = " << currentSprite << std::endl; 
	if (currentSprite < static_cast<int>(sprites.size()))  {
    	Viewport::getInstance().setObjectToTrack(sprites[currentSprite]);
	}
	else {
    	Viewport::getInstance().setObjectToTrack(knightWalk);
	}
} 

void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_T] ) {
          switchSprite();
        }
        if ( keystate[SDL_SCANCODE_M] ) {
          currentStrategy = (currentStrategy + 1) % strategies.size();
        }
        if ( keystate[SDL_SCANCODE_F1] ) {
          hud.setON(!hud.isON());
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:

    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      if( keystate[SDL_SCANCODE_A] ) {
	  	static_cast<Player*>(knightWalk)->left();	  
	  }
      if( keystate[SDL_SCANCODE_D] ) {
	  	static_cast<Player*>(knightWalk)->right();	  
	  }
      if( keystate[SDL_SCANCODE_W] ) {
	  	static_cast<Player*>(knightWalk)->up();	 
	  }
      if( keystate[SDL_SCANCODE_S] ) {
	  	static_cast<Player*>(knightWalk)->down();	  
	  }
	  
	  
	  draw();
      update(ticks);
      
	  if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
