#include "drawFilledCircle.h"

DrawFilledCircle::DrawFilledCircle(SDL_Renderer* r, SDL_Point c, int rad, SDL_Color col) : renderer(r), center(c),radius(rad),color(col) {}

void DrawFilledCircle::draw() const {

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
