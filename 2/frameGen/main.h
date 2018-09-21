#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <math.h>
#include "frameGenerator.h"
#include "drawFilledTriangle.h"
#include "drawFilledCircle.h"
#include "drawFilledRectangle.h"
#include "drawFilledSemiCircle.h"
#include "vector2f.h"

const std::string TITLE = "Floating Island by Vivek Udupa";
const std::string NAME = "vkoodli";

const int WIDTH = 680;
const int HEIGHT = 460;

Vector2f v0{500,100};
Vector2f v1{150,200};
Vector2f v2{350,200};

//Drawing a rectangle
SDL_Rect posi;

int DrawFilledSemiCircle::Id = 0;

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
