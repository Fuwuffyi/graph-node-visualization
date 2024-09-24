#pragma once

#include "simulation.hpp"
#include <SDL2/SDL.h>
#include <string>

class Window {
public:
  Window(const std::string &title, const uint32_t _width,
         const uint32_t _height);
  ~Window();

  void run(Simulation &simulation);

  void handleEvents(std::vector<Node> &nodes);
  void update(Simulation &simulation, const float deltaTime);
  void render(Simulation &simulation);

  void handleKeyDown(const SDL_KeyCode &k);
  void handleMouseButtonDown(const SDL_MouseButtonEvent &e,
                             std::vector<Node> &nodes, const bool isMouseDown);

  uint32_t getWidth() const;
  uint32_t getHeight() const;

private:
  static constexpr uint32_t TARGET_FPS = 300;
  static constexpr uint32_t FRAME_DELAY = 1000 / TARGET_FPS;

  const uint32_t width;
  const uint32_t height;
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool isRunning;
  Node *currentNode;
};
