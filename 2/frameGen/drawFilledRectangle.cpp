#include "drawFilledRectangle.h"

DrawFilledRectangle::DrawFilledRectangle(SDL_Renderer* r, SDL_Rect& p): renderer(r), posi(p) {}

void DrawFilledRectangle::draw() const {
	
	SDL_RenderFillRect (renderer, &posi);
}

/*
void DrawFilledRectangle::operator=(int xpos, int ypos, int height, int width) {
	
	posi.x = xpos;
	posi.y = ypos;
	posi.h = height;
	posi.w = width;
}
	
*/
