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
  
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  gdata(Gamedata::getInstance()),
  rc( RenderContext::getInstance() ),
  io( IoMod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc.getRenderer() ),
  greenSky("greenSky", Gamedata::getInstance().getXmlInt("greenSky/factor") ),
  greenClouds("greenClouds", Gamedata::getInstance().getXmlInt("greenClouds/factor") ),
  greenMountains("greenMountains", Gamedata::getInstance().getXmlInt("greenMountains/factor") ),
  greenBuildings("greenBuildings", Gamedata::getInstance().getXmlInt("greenBuildings/factor") ),
  greenBridge("greenBridge", Gamedata::getInstance().getXmlInt("greenBridge/factor") ),
  greenHouse("greenHouse", Gamedata::getInstance().getXmlInt("greenHouse/factor") ),
  greenGround("greenGround", Gamedata::getInstance().getXmlInt("greenGround/factor") ),
  viewport( Viewport::getInstance() ),
  strategies(std::vector<CollisionStrategy*> {}),
  currentStrategy(0),
  currentSprite(0),
  collision(false),
  sprites(),
  colour({0, 0, 0xff, 0}),
  makeVideo( false ),
  hud(Hud::getInstance())
{
    int n = gdata.getXmlInt("ghost/count"); //Number of ghosts
	sprites.reserve(n+1); //plus 1 for the player
	
	{
	Drawable* s = new Player("knightWalk");
	s->setScale(0.15);
	sprites.push_back(s);
	}	

   Vector2f pos = static_cast<Player*>(sprites[0])->getPosition();
   int w = static_cast<Player*>(sprites[0])->getScaledWidth();
   int h = static_cast<Player*>(sprites[0])->getScaledHeight();

   for (int i = 1; i < n+1; ++i) {
  	 sprites.push_back(new SmartSprite("ghost", pos, w, h) );
     static_cast<Player*>(sprites[0])->attach(static_cast<SmartSprite*>(sprites[i]));
   }

   strategies.push_back( new RectangularCollisionStrategy );
   strategies.push_back( new PerPixelCollisionStrategy );
   strategies.push_back( new MidPointCollisionStrategy );


   Viewport::getInstance().setObjectToTrack(static_cast<Player*>(sprites[0]));
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

  //knightWalk->draw();
  
  hud.draw();

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  checkForCollisions();

  //knightWalk->update(ticks);

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

void Engine::checkForCollisions() {
	collision = false;
	auto it = sprites.begin();
	while( it != sprites.end() ) {
		if( strategies[currentStrategy]->execute(*static_cast<Player*>(sprites[0]), **it) ) {
		collision = true;
		static_cast<Player*>(sprites[0])->collided();
		//SmartSprite* doa = *it;
		Drawable* doa = *it;
		static_cast<Player*>(sprites[0])->detach(static_cast<SmartSprite*>(doa));
		delete doa;
		it = sprites.erase(it);
		}
	else{
	++it;
	static_cast<Player*>(sprites[0])->missed();
	collision = false;
	} 
	}
}

void Engine::switchSprite() {
	++currentSprite;
	currentSprite = currentSprite % (sprites.size());
    Viewport::getInstance().setObjectToTrack(sprites[currentSprite]);
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
        if ( keystate[SDL_SCANCODE_E] ) {
			sprites[currentSprite]->explode();
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
	  	static_cast<Player*>(sprites[0])->left();	  
	  }
      if( keystate[SDL_SCANCODE_D] ) {
	  	static_cast<Player*>(sprites[0])->right();	  
	  }
      if( keystate[SDL_SCANCODE_W] ) {
	  	static_cast<Player*>(sprites[0])->up();	 
	  }
      if( keystate[SDL_SCANCODE_S] ) {
	  	static_cast<Player*>(sprites[0])->down();	  
	  }
	  
	  
	  draw();
      update(ticks);
      
	  if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
