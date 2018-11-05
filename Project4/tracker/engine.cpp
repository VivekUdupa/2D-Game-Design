#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "flyingSaucer.h"
#include "gameData.h"
#include "engine.h"
#include "frameGenerator.h"
#include "player.h"
#include "hud.h"


Engine::~Engine() { 
  delete star;
  delete astronaut;
  delete flyingSaucer;
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
  star(new Sprite("YellowStar")),
  astronaut(new MultiSprite("astronaut")),
  flyingSaucer(new FlyingSaucer("flyingSaucer")),
  knightWalk(new Player("knightWalk")),
  currentSprite(0),
  colour({0, 0, 0xff, 0}),
  makeVideo( false ),
  hud(Hud::getInstance())
{
  astronaut->setScale(0.5);  
  knightWalk->setScale(0.15);  
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



 // star->draw();
  astronaut->draw();
  flyingSaucer->draw();
  knightWalk->draw();

	/*
  //Printing FPS
  std::ostringstream fpsString;
  fpsString << "FPS: " << Clock::getInstance().getFps() << std::endl ;

  IoMod::getInstance().
    writeText(fpsString.str(), msgFPSPos[0], msgFPSPos[1], colour);
  */
  hud.draw();

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  //star->update(ticks);
  astronaut->update(ticks);
  flyingSaucer->update(ticks);
  knightWalk->update(ticks);

  greenSky.update();
  greenClouds.update();
  greenMountains.update();
  greenBuildings.update();
  greenBridge.update();
  greenHouse.update();
  greenGround.update();
 
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  ++currentSprite;
  currentSprite = currentSprite % 3;
  if ( currentSprite == 1) {
    Viewport::getInstance().setObjectToTrack(astronaut);
  }
  else if(currentSprite == 2) {
    Viewport::getInstance().setObjectToTrack(flyingSaucer);
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
