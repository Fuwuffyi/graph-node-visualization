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
  Simulation(const float width_, const float height_,
             const std::vector<Node> &nodes_);
  Simulation(const float width_, const float height_);

  void addNode(const Node &node);
  void addLink(const Node &nodeA, const Node &nodeB);

  void update(const float deltaTime);
  void render(SDL_Renderer *renderer) const;

private:
  // Simulation visualization parameters
  static constexpr glm::tvec4<uint8_t> LINK_COLOR =
      glm::tvec4<uint8_t>(120, 120, 120, 255); // The node's link line color
  static constexpr glm::tvec4<uint8_t> NODE_OUTLINE =
      glm::tvec4<uint8_t>(0, 255, 255, 150); // Node's outline color in RGBA
  static constexpr glm::tvec4<uint8_t> NODE_FILL =
      glm::tvec4<uint8_t>(255, 255, 255, 255);  // Node's inner color in RGBA
  static constexpr float LINK_THICKNESS = 4.0f; // Thickness of the link line
  static constexpr float NODE_SIZE_MULTIPLIER =
      12.0f; // Node's radius multiplier
             // Simulation physics parameters
  static constexpr float VELOCITY_DAMPING =
      0.99f; // Multiplies the velocity every frame (0.0f - 1.0f)
  static constexpr float CENTER_ATTRACTION_FORCE_MULT =
      200.0f; // Multiplies the center attraction force
  static constexpr float REPULSION_FORCE_MULT = 400.0f;

private:
  // Actual needed variables
  const glm::vec2 dimensions;
  const glm::vec2 translation;
  std::vector<Node> nodes;
  std::vector<Link_t> links;
};
