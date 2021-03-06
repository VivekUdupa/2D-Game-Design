#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "flyingSaucer.h"
#include "rocket.h"
#include "gameData.h"
#include "engine.h"
#include "frameGenerator.h"

Engine::~Engine() { 
  delete star;
  delete astronaut;
  delete flyingSaucer;
  delete rocket;
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
  msgFPSPos(
    Vector2f( gdata.getXmlInt("viewFPS/loc/x"), gdata.getXmlInt("viewFPS/loc/y") )
  ),
  world("back", Gamedata::getInstance().getXmlInt("back/factor") ),
  planetsBig("planetsBig", Gamedata::getInstance().getXmlInt("planetsBig/factor") ),
  planetsSmall("planetsSmall", Gamedata::getInstance().getXmlInt("planetsSmall/factor") ),
  viewport( Viewport::getInstance() ),
  star(new Sprite("YellowStar")),
  astronaut(new MultiSprite("astronaut")),
  flyingSaucer(new FlyingSaucer("flyingSaucer")),
  rocket(new Rocket("rocket")),
  currentSprite(0),
  colour({0, 0, 0xff, 0}),
  makeVideo( false )
{
  astronaut->setScale(0.5);  
  Viewport::getInstance().setObjectToTrack(rocket);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  world.draw();
  planetsBig.draw();
  planetsSmall.draw();

 // star->draw();
  astronaut->draw();
  flyingSaucer->draw();
  rocket->draw();

	
  //Printing FPS
  std::ostringstream fpsString;
  fpsString << "FPS: " << Clock::getInstance().getFps() << std::endl ;

  IoMod::getInstance().
    writeText(fpsString.str(), msgFPSPos[0], msgFPSPos[1], colour);
  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  //star->update(ticks);
  astronaut->update(ticks);
  flyingSaucer->update(ticks);
  rocket->update(ticks);
  world.update();
  planetsBig.update();
  planetsSmall.update();
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
    Viewport::getInstance().setObjectToTrack(rocket);
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
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
