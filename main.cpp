#include "include/window.hpp"

constexpr uint32_t SCREEN_WIDTH = 900;
constexpr uint32_t SCREEN_HEIGHT = 900;

int main() {
  Window window("SDL Grapher", SCREEN_WIDTH, SCREEN_HEIGHT);
  window.run();
  return 0;
}
