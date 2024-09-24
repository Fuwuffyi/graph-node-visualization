#include "../include/window.hpp"

#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <csignal>
#include <glm/common.hpp>
#include <iostream>

Window::Window(const std::string &title, const uint32_t _width,
               const uint32_t _height)
    : width(_width), height(_height), window(nullptr), renderer(nullptr),
      isRunning(true), currentNode(nullptr) {
  // Init SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
              << std::endl;
    isRunning = false;
    return;
  }
  // Create the window
  window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, static_cast<int32_t>(width),
                            static_cast<int32_t>(height), SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    isRunning = false;
    SDL_Quit();
    return;
  }
  // Create the renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr) {
    std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    isRunning = false;
    return;
  }
  TTF_Init();
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Window::~Window() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Window::run(Simulation &simulation) {
  uint32_t previousTime = SDL_GetTicks();
  while (isRunning) {
    // Handle all events
    handleEvents(simulation.getEditableNodes());
    if (!isRunning) {
      break;
    }
    // Calculate deltatime
    const uint32_t currentTime = SDL_GetTicks();
    const uint32_t frameTime = currentTime - previousTime;
    const float deltaTime = static_cast<float>(frameTime) / 1000.0f;
    previousTime = currentTime;
    // Update screen
    update(simulation, deltaTime);
    // Make selected node follow mouse
    if (currentNode != nullptr) {
      int32_t x, y;
      SDL_GetMouseState(&x, &y);
      currentNode->setPosition(glm::vec2(x - width / 2.0f, y - height / 2.0f));
    }
    render(simulation);
    // Set FPS cap
    const uint32_t frameDuration = SDL_GetTicks() - currentTime;
    if (frameDuration < FRAME_DELAY) {
      SDL_Delay(FRAME_DELAY - frameDuration);
    }
  }
}

void Window::handleEvents(std::vector<Node> &nodes) {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    switch (event.type) {
    case SDL_QUIT:
      isRunning = false;
      break;
    case SDL_KEYDOWN:
      handleKeyDown(static_cast<SDL_KeyCode>(event.key.keysym.sym));
      break;
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
      handleMouseButtonDown(event.button, nodes,
                            event.type == SDL_MOUSEBUTTONDOWN);
      break;
    default:
      break;
    }
  }
}

void Window::update(Simulation &simulation, const float deltaTime) {
  simulation.update(deltaTime);
}

void Window::render(Simulation &simulation) {
  SDL_SetRenderDrawColor(renderer, 0x05, 0x07, 0x1D, 0xFF);
  SDL_RenderClear(renderer);
  simulation.render(renderer);
  SDL_RenderPresent(renderer);
}

void Window::handleKeyDown(const SDL_KeyCode &k) {
  if (k == SDLK_ESCAPE) {
    isRunning = false;
  }
}

void Window::handleMouseButtonDown(const SDL_MouseButtonEvent &e,
                                   std::vector<Node> &nodes,
                                   const bool isMouseDown) {
  if (isMouseDown) {
    for (Node &n : nodes) {
      const float dist = glm::distance(
          n.getPosition(), glm::vec2(e.x - width / 2.0f, e.y - height / 2.0f));
      if (dist < 20.0f) {
        currentNode = &n;
      }
    }
  } else {
    currentNode = nullptr;
  }
}
