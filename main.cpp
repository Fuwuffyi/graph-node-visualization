#include "include/window.hpp"

#include <random>

constexpr uint32_t SCREEN_WIDTH = 1600;
constexpr uint32_t SCREEN_HEIGHT = 900;

int main() {
  // Create the node simulation
  Simulation simulation(SCREEN_WIDTH, SCREEN_HEIGHT);
  // Add random nodes
  constexpr uint32_t count = 200;
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<uint32_t> nDistr(0, count - 1);
  std::uniform_real_distribution<float> uDistr(0.0f, 1.0f);
  std::uniform_real_distribution<float> wDistr(
      -static_cast<float>(SCREEN_HEIGHT) / 6.0f,
      static_cast<float>(SCREEN_WIDTH) / 6.0f);
  std::uniform_real_distribution<float> hDistr(
      -static_cast<float>(SCREEN_HEIGHT) / 6.0f,
      static_cast<float>(SCREEN_HEIGHT) / 6.0f);
  for (uint32_t i = 0; i < count; ++i) {
    simulation.addNode(
        Node(i, 1.0f, glm::vec2(wDistr(generator), hDistr(generator))));
  }
  // Add random connections
  for (uint32_t i = 0; i < 400; ++i) {
    simulation.addLink(nDistr(generator), nDistr(generator));
  }
  // Create the window and run the simulation
  Window window("SDL Grapher", SCREEN_WIDTH, SCREEN_HEIGHT);
  window.run(simulation);
  return 0;
}
