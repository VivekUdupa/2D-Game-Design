#include <iostream>
#include <SDL2/SDL.h>
#include "vector2f.h"
#include <SDL_ttf.h>

class DrawFilledCircle{
public:
	DrawFilledCircle(SDL_Renderer*, SDL_Point, int, SDL_Color);
	void draw() const;

private:
	SDL_Renderer* renderer;
	SDL_Point center;
	int radius;
	SDL_Color color; 
};
