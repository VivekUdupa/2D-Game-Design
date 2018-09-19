#include <string>
#include <SDL.h>
//#include "all.h"

class FrameGenerator {
public:
  FrameGenerator(SDL_Renderer*, SDL_Window*, int, int, const std::string&);
  void makeFrame();
private:
  SDL_Renderer* const renderer;
  SDL_Window* const window;
//  SDL_Window* const window2;
  const int WIDTH;
  const int HEIGHT;
  const std::string USERNAME;
  FrameGenerator(const FrameGenerator&);
  FrameGenerator& operator=(const FrameGenerator&);
};
