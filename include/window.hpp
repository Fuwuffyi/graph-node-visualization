#pragma once

#include <SDL2/SDL.h>
#include <string>

class Window {
public:
  Window(const std::string &title, const uint32_t width, const uint32_t height);
  ~Window();

  void run();

  void handleEvents();
  void update();
  void render();

  void handleKeyDown(const SDL_KeyCode &k);
  void handleMouseButtonDown(const SDL_MouseButtonEvent &e);

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool isRunning;
};
