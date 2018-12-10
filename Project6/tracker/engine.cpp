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
#include "hudProj.h"
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
  player(),
  //zombie(new TwoWayMultiSprite("zombie")),
  colour({0, 0, 0xff, 0}),
  makeVideo( false ),
  hud(Hud::getInstance()),
  hudProj(HudProj::getInstance())
{
   
   //zombie->setScale(0.48);
   //zombie->setVelocityY(0);
    int n = gdata.getXmlInt("ghost/count"); //Number of ghosts
	//sprites.reserve(n+1); 
	
	{
	ShootingSprite* p = new ShootingSprite("knightWalk");
	p->setScale(0.10);
	player.push_back(p);
	}	

   Vector2f pos = player[0]->getPosition();
   int w = player[0]->getScaledWidth();
   int h = player[0]->getScaledHeight();

  
   for (int i = 0; i < n; ++i) {
  	 sprites.push_back(new SmartSprite("ghost", pos, w, h) );
     //player[0]->attach(sprites[i]);
   }

   SmartSprite* s = new SmartSprite("zombie", pos, w, h);
   sprites.push_back(s);
   s->setVelocityY(0);
   s->setScale(0.47);
   player[0]->attach(s);
   
   for (unsigned int i = 0; i < sprites.size(); ++i) {
   		player[0]->attach(sprites[i]);
   }
   

   strategies.push_back( new PerPixelCollisionStrategy );
   strategies.push_back( new RectangularCollisionStrategy );
   strategies.push_back( new MidPointCollisionStrategy );
	
//	std::cout << "Y distance = " << player[0]->getY() << std::endl;

   Viewport::getInstance().setObjectToTrack(player[0]);
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
	
 for (const Player* p : player) {
 	p->draw();
 }

 for (const Drawable* sprite : sprites) {
 	sprite->draw();
 }

	
  strategies[currentStrategy]->draw();
  
  hud.draw();
  hudProj.draw(player[0]->getActiveProj(), player[0]->getFreeProj());

/*
 std::stringstream strm;
 strm << "Ghosts Remaining: " << sprites.size() << std::endl;
 io.writeText(strm.str(), 30, 60);
*/

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  checkForCollisions();

  //knightWalk->update(ticks);
  for (Player* p : player) {
  	p->update(ticks);
  }

	if(sprites.size()!=0) {
  		for (Drawable* sprite : sprites) {
  		sprite->update(ticks);
 	 }
	}

  //zombie->update(ticks);
  
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
	if( strategies[currentStrategy]->execute(*player[0], **it) ) {
		collision = true;
		player[0]->collided();
		player[0]->explode();
		
		SmartSprite* doa = *it;
		player[0]->detach(doa);
		delete doa;
		it = sprites.erase(it);
		

		}
	else if( player[0]->collidedWith((*it)) ) {
		(*it)->explode();
		(*it)->collide();
		player[0]->missed();
		collision = false;
	}
	else{
		++it;
		player[0]->missed();
		collision = false;
	}
/*
	auto sp = sprites.begin();
	while (sp != sprites.end()) {
		if( (*sp)->killSprites() ) {
			//(*sp)->explode();
			player[0]->detach( (*sp) );
			delete (*sp);
			sp = sprites.erase(sp);
		}
		else{
			++sp;
		}
		}
*/

	}
}

/*
void Engine::checkForCollisions() {
	collision = false;
	auto it = sprites.begin();
	while( it != sprites.end() ) {
		//if(!(player[0]->shooting())) {
		//	for(auto bul : player[0]->getBulletList()) {
				//if(strategies[currentStrategy]->execute(bul, **it)) {
		//		if(player[0]->collidedWith(*it)){
		//			(*it)->explode();
					//player[0]->detach(*it);
					//delete *it;
					//it = sprites.erase(it);
		//			}
				
		//		else {
		//			++it;
		//		}
		//	}
		//}
		
		if( strategies[currentStrategy]->execute(*player[0], **it) ) {
		collision = true;
		player[0]->collided();
		player[0]->explode();
		SmartSprite* doa = *it;

   		std::cout << "Sprite is: " << player[0]->getName() << std::endl;
		
		//doa->explode();
		//if(player[0]->collidedWith(doa)){
		//	doa[currentSprite].explode();
		//}
		//Drawable* doa = *it;
		player[0]->detach(doa);
		delete doa;
		it = sprites.erase(it);
		}
	else{
	++it;
	player[0]->missed();
	collision = false;
	} 
	//}
	auto sp = sprites.begin();
		while(sp!=sprites.end() ){
			if(player[0]->collidedWith(*sp)) {
				(*sp)->explode();
				delete (*sp);
				sp = sprites.erase(sp);
			}
			else{
				++sp;
			}

			}
		}
	}
*/

void Engine::switchSprite() {
	++currentSprite;
	currentSprite = currentSprite % (player.size());
	//currentSprite = currentSprite % (sprites.size());
    Viewport::getInstance().setObjectToTrack(player[currentSprite]);
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
			//sprites[currentSprite]->explode();
			player[currentSprite]->explode();
		}
        if ( keystate[SDL_SCANCODE_F1] ) {
          hud.setON(!hud.isON());
        }
        if ( keystate[SDL_SCANCODE_F2] ) {
          hudProj.setON(!hudProj.isON());
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
	  	if(keystate[SDL_SCANCODE_SPACE]){
			player[0]->jump();
	  	}
	  	if(keystate[SDL_SCANCODE_LSHIFT]){
			std::cout << "Shoot Pressed" << std::endl;
			player[0]->shoot();
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
	  	player[0]->left();	  
	  }
      if( keystate[SDL_SCANCODE_D] ) {
	  	player[0]->right();	  
	  }
      if( keystate[SDL_SCANCODE_W] ) {
	  	player[0]->up();	 
	  }
      if( keystate[SDL_SCANCODE_S] ) {
	  	player[0]->down();	  
	  }
	  
	  
	  draw();
      update(ticks);
      
	  if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
