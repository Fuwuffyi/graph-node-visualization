#include "include/simulation.hpp"
#include "include/window.hpp"

constexpr uint32_t SCREEN_WIDTH = 900;
constexpr uint32_t SCREEN_HEIGHT = 900;

int main() {
  // Create the node simulation
  Simulation simulation;
  simulation.addNode(Node("Test", 1.0f, glm::vec2(450.0f)));
  simulation.addNode(Node("Test1", 1.0f, glm::vec2(250.0f)));
  simulation.addNode(Node("Test2", 1.0f, glm::vec2(800.0f)));
  // Create the window and run the simulation
  Window window("SDL Grapher", SCREEN_WIDTH, SCREEN_HEIGHT);
  window.run(simulation);
  return 0;
}
