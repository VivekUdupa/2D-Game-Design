#include "drawFilledSemiCircle.h"

DrawFilledSemiCircle::DrawFilledSemiCircle(SDL_Renderer* r, SDL_Point c, int rad, SDL_Color col, int w, int h) : renderer(r), center(c),radius(rad),color(col), WIDTH(w), HEIGHT(h), uniqId(Id++) {}

/*
DrawFilledSemiCircle::DrawFilledSemiCircle(DrawFilledSemiCircle &p)
{
	renderer = p.renderer;
	center = p.center;
	radius = p.radius;
	color = p.color;
	WIDTH = p.WIDTH;
	HEIGHT = p.HEIGHT;
	
}
*/

void DrawFilledSemiCircle::draw() const {
  	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	int startX = center.x - radius; //Starting point of the circle

	if(startX < 0)
	{
		startX = 0; //Clip to start of frame
	}
	
	int endX = center.x + radius; //End point of the circle
	
	if(endX > WIDTH)
	{
		endX = WIDTH; //Clip to end of frame
	}
 	
	int startY = center.y;
	int endY;
	for (int k = startX; k <= endX; k++)
	{
		
		endY = startY - (int) sqrt((radius*radius) - ((k-center.x)*(k-center.x))) ; //Corresponding Y points	
	//	std::cout << "(Start, End) point:" << k << "," << endY << std::endl;
		SDL_RenderDrawLine(renderer, k, startY, k, endY); //Fill Circle with lines 
	}

}

std::ostream& operator<<(std::ostream& out, const DrawFilledSemiCircle& semiC)
{
	out << "center of cloud " << semiC.uniqId << " is: ( " << semiC.center.x << "," << semiC.center.y << ")" << std::endl; 
	return out;
}
