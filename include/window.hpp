#pragma once

#include <SDL2/SDL.h>
#include <string>

class Window {
public:
  Window(const std::string &title, const uint32_t width, const uint32_t height);
  ~Window();

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool isRunning;
};
