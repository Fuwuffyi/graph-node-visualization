#include "include/simulation.hpp"
#include "include/window.hpp"

#include <random>

constexpr uint32_t SCREEN_WIDTH = 900;
constexpr uint32_t SCREEN_HEIGHT = 900;

int main() {
  // Create the node simulation
  Simulation simulation;
  // Add random nodes
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_real_distribution<float> wDistr(0.0f, SCREEN_WIDTH);
  std::uniform_real_distribution<float> hDistr(0.0f, SCREEN_HEIGHT);
  for (uint32_t i = 0; i < 30; ++i) {
    simulation.addNode(Node(&"Node "[i], 1.0f,
                            glm::vec2(wDistr(generator), hDistr(generator))));
  }
  // Create the window and run the simulation
  Window window("SDL Grapher", SCREEN_WIDTH, SCREEN_HEIGHT);
  window.run(simulation);
  return 0;
}
