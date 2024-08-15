#include "../include/window.hpp"

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
}

Window::~Window() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Window::run() {
  while (isRunning) {
    handleEvents();
    update();
    render();
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
    }
  }
}

void Window::update() {
  // TODO:
}

void Window::render() {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(renderer);
  // TODO:
  SDL_RenderPresent(renderer);
}

void Window::handleKeyDown(const SDL_KeyCode &k) {
  if (k == SDLK_ESCAPE) {
    isRunning = false;
  }
}

void Window::handleMouseButtonDown(const SDL_MouseButtonEvent &e) {
  if (e.button == SDL_BUTTON_LEFT) {
    std::cout << "Left mouse button clicked at (" << e.x << ", " << e.y << ")"
              << std::endl;
  }
}
