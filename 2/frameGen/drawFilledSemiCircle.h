#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <math.h>

//const int WIDTH = 680;
//const int HEIGHT = 460;

class DrawFilledSemiCircle{

public:
	DrawFilledSemiCircle(SDL_Renderer*, SDL_Point, int, SDL_Color, int, int);

//	std::ostream& operator<< (std::ostream&, const const const const const const const const DrawFilledSemiCircle&);  //output overload
	
friend std::ostream& operator<<(std::ostream& out, const DrawFilledSemiCircle& semiC);

	void draw() const;
	
	~DrawFilledSemiCircle() {}; //Destructor
	
	

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
};
