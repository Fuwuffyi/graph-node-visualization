#include "../include/window.hpp"

#include <SDL2/SDL_timer.h>
#include <csignal>
#include <glm/common.hpp>
#include <iostream>

Window::Window(const std::string &title, const uint32_t width,
               const uint32_t height)
    : window(nullptr), renderer(nullptr), isRunning(true) {
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
    handleEvents();
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
    render(simulation);
    // Set FPS cap
    const uint32_t frameDuration = SDL_GetTicks() - currentTime;
    if (frameDuration < FRAME_DELAY) {
      SDL_Delay(FRAME_DELAY - frameDuration);
    }
  }
}

void Window::handleEvents() {
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
      handleMouseButtonDown(event.button);
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
  SDL_SetRenderDrawColor(renderer, 0x30, 0x30, 0x30, 0xFF);
  SDL_RenderClear(renderer);
  simulation.render(renderer);
  SDL_RenderPresent(renderer);
}

void Window::handleKeyDown(const SDL_KeyCode &k) {
  if (k == SDLK_ESCAPE) {
    isRunning = false;
  }
}

void Window::handleMouseButtonDown(const SDL_MouseButtonEvent &e) {
  // TODO: Make nodes move with mouse?
  if (e.button == SDL_BUTTON_LEFT) {
    std::cout << "Left mouse button clicked at (" << e.x << ", " << e.y << ")"
              << std::endl;
  }
}
