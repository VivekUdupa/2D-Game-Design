#include <iostream>
#include <SDL2/SDL.h>
#include "vector2f.h"
#include <SDL_ttf.h>

class DrawFilledRectangle {
public:
	DrawFilledRectangle(SDL_Renderer*, SDL_Rect&);

	void draw() const;

//SDL_Rect operator=(int x, int y, int h, int w);

private:
	SDL_Renderer* renderer;
	SDL_Rect posi;
	//int x, y, h, w;

};
