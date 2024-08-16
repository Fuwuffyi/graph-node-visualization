#pragma once

#include "node.hpp"
#include <SDL2/SDL.h>
#include <vector>

class Simulation {
private:
  typedef struct Link {
    const uint32_t idxNodeA;
    const uint32_t idxNodeB;
  } Link_t;

public:
  Simulation(const std::vector<Node> &nodes_);
  Simulation();

  void addNode(const Node &node);
  void addLink(const Node &nodeA, const Node &nodeB);

  void update(const float deltaTime);
  void render(SDL_Renderer *renderer) const;

private:
  // Simulation visualization parameters
  static constexpr glm::tvec4<uint8_t> LINK_COLOR =
      glm::tvec4<uint8_t>(120, 120, 120, 255);
  static constexpr glm::tvec4<uint8_t> NODE_OUTLINE =
      glm::tvec4<uint8_t>(0, 255, 255, 150);
  static constexpr glm::tvec4<uint8_t> NODE_FILL =
      glm::tvec4<uint8_t>(255, 255, 255, 255);
  // Simulation physics parameters

private:
  // Actual needed variables
  std::vector<Node> nodes;
  std::vector<Link_t> links;
};
