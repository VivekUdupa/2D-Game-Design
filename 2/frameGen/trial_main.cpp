#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include "frameGenerator.h"
#include "drawFilledTriangle.h"
#include "drawFilledCircle.h"
#include "drawFilledRectangle.h"

const std::string TITLE = "Vivek Udupa's Best Try";
const std::string NAME = "vkoodli";

const int WIDTH = 640;
const int HEIGHT = 480;

Vector2f v0{500,100};
Vector2f v1{150,200};
Vector2f v2{350,200};


void drawRect( SDL_Renderer* renderer, SDL_Rect& position, SDL_Color color, int mode);

void drawCircle(SDL_Renderer* renderer,
  SDL_Point center, int radius, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  for (int w = 0; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      int dx = radius - w; // horizontal offset
      int dy = radius - h; // vertical offset
      if ((dx*dx + dy*dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
      }
    }
  }
}


//Drawing a rectangle
SDL_Rect posi;

void writeName(SDL_Renderer* renderer) {
  TTF_Init();
  TTF_Font* font = TTF_OpenFont("fonts/arial.ttf", 24);
  if (font == NULL) {
    throw std::string("error: font not found");
  }
  SDL_Color textColor = {0xff, 0, 0, 0};
  SDL_Surface* surface = 
    TTF_RenderText_Solid(font, TITLE.c_str(), textColor);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  int textWidth = surface->w;
  int textHeight = surface->h;
  SDL_FreeSurface(surface);
  SDL_Rect dst = {20, HEIGHT-40, textWidth, textHeight};

  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}

/*
//Function to draw rectangle
void drawRect( SDL_Renderer* renderer, SDL_Rect& position, SDL_Color color, int mode)
{
  	position.x = 400;
  	position.y = 100;
  	position.h = 40;
  	position.w = 40;

	//Set the rectangle color
  	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	// mode = 1 -> Fill rectangle, else outline rectangle
	if(mode == 1)
	{
		SDL_RenderFillRect( renderer, &posi);
	}
	else
	{
		SDL_RenderDrawRect( renderer, &posi );
	}
}

*/

int main(void) {
  try {
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
      std::cout << "Failed to initialize SDL2" << std::endl;
      return EXIT_FAILURE;
    }
    SDL_Window* window = SDL_CreateWindow(
      TITLE.c_str(),
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      WIDTH,
      HEIGHT,
      SDL_WINDOW_SHOWN
    );
    
    // Apparently we can't use hardware acceleration with
    // SDL_GetWindowSurface
    SDL_Renderer* renderer = SDL_CreateRenderer( 
      window, -1, SDL_RENDERER_SOFTWARE
    );

    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Drawing concentric circles

    SDL_Point center = {320, 240};
    SDL_Color color1 = {255,0,0,255};
    SDL_Color color2 = {0,255,0,255};
    SDL_Color color3 = {255,0,255,255};
    drawCircle(renderer, center, 90, color1);
    drawCircle(renderer, center, 70, color2);
    drawCircle(renderer, center, 50, color3);


	//Drawing a triangle
/*	
    	SDL_SetRenderDrawColor(renderer, 212, 175, 55, 255); //Metallic Gold
	
	SDL_RenderDrawLine( renderer, 150, 100, 150, 200 );
	SDL_RenderDrawLine( renderer, 150, 200, 350, 200 );
	SDL_RenderDrawLine( renderer, 350, 200, 150, 100 );

	SDL_RenderPresent( renderer );
    	SDL_SetRenderDrawColor(renderer, 0, 175, 0, 255); //Fill color 
		int x1 = 150, count = 0;
		for (int y1 = 100; y1 < 200; y1++)
		{
			++count;
			for(int dx = 0; dx < count ; dx++ )
			{
				if( (x1 = 150 + dx) < 150 + count)
					SDL_RenderDrawPoint( renderer, x1,y1);
				if( (x1 = 150 - dx) > 150 )
					SDL_RenderDrawPoint( renderer, x1,y1);
			}

				SDL_RenderPresent( renderer );
		}

*/
		
    	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
		DrawFilledTriangle triangle( renderer, v0, v1, v2);
		triangle.draw();
		SDL_RenderPresent( renderer );


/*	
	SDL_RenderDrawLine( renderer, 250, 102, 152, 198 );
	SDL_RenderDrawLine( renderer, 152, 198, 348, 198 );
	SDL_RenderDrawLine( renderer, 348, 198, 250, 102 );

	SDL_RenderPresent( renderer );

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
		//Vertical grid
		for(int a = 0; a < WIDTH; a+=20)
		{
			SDL_RenderDrawLine( renderer, a, 0, a, HEIGHT );
			SDL_RenderPresent( renderer );
		}
		//Horizontal grid
		for(int b = 0; b < WIDTH; b+=20)
		{
			SDL_RenderDrawLine( renderer, 0, b, WIDTH, b );
			SDL_RenderPresent( renderer );
		}
*/
    //rectangle
	posi.x = 200;	
	posi.y = 300;	
	posi.h = 190;	
	posi.w = 190;	

	    
  //  	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//SDL_RenderDrawRect( renderer, &posi );
//	SDL_RenderFillRect( renderer, &posi);
//	drawRect( renderer, posi, color4, 1);
		
    	SDL_SetRenderDrawColor(renderer, 250, 50, 50, 255);
		DrawFilledRectangle rect1(renderer, posi);
		rect1.draw();
    	SDL_RenderPresent(renderer);
	
    	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	//Draw a verticle line in the center
	SDL_RenderDrawLine( renderer, WIDTH/2, 0, WIDTH/2,HEIGHT );
	SDL_RenderPresent(renderer);
   

	


//***************************************************************************//
    writeName(renderer);
    SDL_RenderPresent(renderer);
    FrameGenerator frameGen(renderer, window, WIDTH, HEIGHT, NAME);
    frameGen.makeFrame();

    SDL_Event event;
    const Uint8* keystate;

	  while ( true ) {
      keystate = SDL_GetKeyboardState(0);
      if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
      if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          break;
        }
		if(event.type == SDL_MOUSEMOTION)
		{
			std::cout << event.motion.x << "," << event.motion.y << '\n';
		}
      }
  }


  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  }
  catch (const std::string& msg) { std::cout << msg << std::endl; }
  catch (...) {
    std::cout << "Oops, someone threw an exception!" << std::endl;
  }
  return EXIT_SUCCESS;
}
