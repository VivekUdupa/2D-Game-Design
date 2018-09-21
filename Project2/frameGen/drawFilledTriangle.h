#include <iostream>
#include <SDL2/SDL.h>
#include "vector2f.h"

class DrawFilledTriangle {
public:
  //DrawFilledTriangle(SDL_Window*, SDL_Renderer*, const Vector2f&, const Vector2f&, const Vector2f&);
  DrawFilledTriangle( SDL_Renderer*,const Vector2f&, const Vector2f&, const Vector2f&, SDL_Color);
  void draw() const;
private:
 // SDL_Window* window;
  SDL_Renderer* renderer;
  Vector2f v0;
  Vector2f v1;
  Vector2f v2;
  SDL_Color color;
  float triangle(Vector2f, float) const;
  float wedge(Vector2f, Vector2f) const;
  int smallest(int, int, int) const;
  int largest(int, int, int) const;
};
