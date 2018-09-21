#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <math.h>

//const int WIDTH = 680;
//const int HEIGHT = 460;

class DrawFilledSemiCircle{

public:
	DrawFilledSemiCircle(SDL_Renderer*, SDL_Point, int, SDL_Color, int, int);

	DrawFilledSemiCircle(DrawFilledSemiCircle &);

	friend std::ostream& operator<<(std::ostream& out, const DrawFilledSemiCircle& semiC);

	void draw() const;
	
	//~DrawFilledSemiCircle() {}; //Destructor
	
	
/*
private:
	SDL_Renderer* renderer;
public:
	SDL_Point center;
	int radius;
private:
	SDL_Color color; 
	int WIDTH;
	int HEIGHT;
public:
	int uniqId;
private:
	static int Id;
*/
private:
	SDL_Renderer* renderer;
	SDL_Point center;
	int radius;
	SDL_Color color;
	int WIDTH;
	int HEIGHT;
	static int Id;
	int uniqId;

};
