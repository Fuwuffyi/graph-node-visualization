#pragma once

#include "simulation.hpp"
#include <SDL2/SDL.h>
#include <string>

class Window {
public:
  Window(const std::string &title, const uint32_t width, const uint32_t height);
  ~Window();

  void run(Simulation &simulation);

  void handleEvents();
  void update(Simulation &simulation);
  void render(Simulation &simulation);

  void handleKeyDown(const SDL_KeyCode &k);
  void handleMouseButtonDown(const SDL_MouseButtonEvent &e);

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool isRunning;
};
