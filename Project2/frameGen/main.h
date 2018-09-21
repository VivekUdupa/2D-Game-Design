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

const int WIDTH = 640;
const int HEIGHT = 480;

Vector2f v0{500,100};
Vector2f v1{150,200};
Vector2f v2{350,200};

int DrawFilledSemiCircle::Id = 0;

void writeName(SDL_Renderer* renderer) {
  TTF_Init();
  TTF_Font* font = TTF_OpenFont("fonts/arial.ttf", 24);
  if (font == NULL) {
    throw std::string("error: font not found");
  }
  SDL_Color textColor = {0x80, 0, 0, 0};
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

// Define Colors
SDL_Color dimGrey = {105, 105, 105, 255};
SDL_Color darkGrey = { 169, 169, 169, 255}; 
SDL_Color lightGrey = { 211, 211, 211, 255}; 
SDL_Color silverGrey = { 192, 192, 192, 255}; 
SDL_Color grey = { 128, 128, 128, 255}; 
SDL_Color smoke = { 245, 245, 245, 255}; 

SDL_Color slDarkGreen = {10, 140, 10, 255};
SDL_Color darkGreen = {0, 100, 0, 255};
SDL_Color green = {0, 128, 0, 255};
SDL_Color forestGreen = {34, 139, 34, 255};
SDL_Color limeGreen = {50, 205, 50, 255};
SDL_Color springGreen = {0, 255, 127, 255};
SDL_Color yellowGreen = {154, 205, 50, 255};

SDL_Color darkGreen20 = {0, 120, 0, 255};
SDL_Color green20 = {0, 148, 0, 255};
SDL_Color forestGreen20 = {34, 159, 34, 255};
SDL_Color darkGreen40 = {0, 140, 0, 255};
SDL_Color green40 = {0, 168, 0, 255};
SDL_Color forestGreen40 = {34, 179, 34, 255};

SDL_Color chocolateBrown = {210, 105, 30, 255};
SDL_Color sandyBrown = {244, 164, 96, 255};
SDL_Color saddleBrown = {139, 69, 19, 255};
SDL_Color sienna = {160, 82, 45, 255};


void DrawBase(SDL_Renderer* renderer);
void DrawGrass(SDL_Renderer* renderer);
void DrawTree(SDL_Renderer* renderer);
void DrawMountain(SDL_Renderer* renderer);
void DrawClouds(SDL_Renderer* renderer, SDL_Point center, int radius, SDL_Color color);
