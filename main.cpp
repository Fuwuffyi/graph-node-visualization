#include "include/simulation.hpp"
#include "include/window.hpp"

#include <random>

constexpr uint32_t SCREEN_WIDTH = 900;
constexpr uint32_t SCREEN_HEIGHT = 900;

int main() {
  // Create the node simulation
  Simulation simulation(SCREEN_WIDTH, SCREEN_HEIGHT);
  // Add random nodes
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_real_distribution<float> wDistr(
      -static_cast<float>(SCREEN_HEIGHT) / 2.0f,
      static_cast<float>(SCREEN_WIDTH) / 2.0f);
  std::uniform_real_distribution<float> hDistr(
      -static_cast<float>(SCREEN_HEIGHT) / 2.0f,
      static_cast<float>(SCREEN_HEIGHT) / 2.0f);
  for (uint32_t i = 0; i < 30; ++i) {
    simulation.addNode(Node(&"Node "[i], 1.0f,
                            glm::vec2(wDistr(generator), hDistr(generator))));
  }
  // Create the window and run the simulation
  Window window("SDL Grapher", SCREEN_WIDTH, SCREEN_HEIGHT);
  window.run(simulation);
  return 0;
}
