#pragma once

#include "link.hpp"
#include "node.hpp"
#include <SDL2/SDL.h>
#include <unordered_set>
#include <vector>

class Simulation {
public:
  Simulation(const float width_, const float height_,
             const std::vector<Node> &nodes_);
  Simulation(const float width_, const float height_);

  void addNode(const Node &node);
  void addLink(const uint32_t indexA, const uint32_t indexB);
  void addLinks(const std::unordered_set<Link> &linksToAdd);

  void update(const float deltaTime);
  void render(SDL_Renderer *renderer) const;

  const std::vector<Node> &getNodes() const;
  const std::unordered_set<Link> &getLinks() const;

private:
  // Simulation visualization parameters
  static constexpr glm::tvec4<uint8_t> LINK_COLOR =
      glm::tvec4<uint8_t>(129, 129, 234, 50); // The node's link line color
  static constexpr glm::tvec4<uint8_t> NODE_OUTLINE =
      glm::tvec4<uint8_t>(209, 53, 221, 100); // Node's outline color in RGBA
  static constexpr glm::tvec4<uint8_t> NODE_FILL =
      glm::tvec4<uint8_t>(111, 24, 143, 255); // Node's inner color in RGBA
  static constexpr glm::tvec4<uint8_t> TEXT_COLOR =
      glm::tvec4<uint8_t>(223, 223, 250, 255);  // Node index text color
  static constexpr float LINK_THICKNESS = 1.0f; // Thickness of the link line
  static constexpr float NODE_SIZE_MULTIPLIER =
      10.0f; // Node's radius multiplier
             // Simulation physics parameters
  static constexpr float VELOCITY_DAMPING =
      0.99f; // Multiplies the velocity every frame (0.0f - 1.0f)
  static constexpr float CENTER_ATTRACTION_FORCE_MULT =
      80.0f; // Multiplies the center attraction force
  static constexpr float REPULSION_FORCE_MULT = 360.0f;
  static constexpr float ATTRACTION_FORCE_MULT = 340.0f;
  static constexpr float ATTRACTION_DISTANCE_TRESHOLD =
      40.0f; // Maximum distance at which there is no attraction

private:
  // Actual needed variables
  const glm::vec2 dimensions;
  const glm::vec2 translation;
  std::vector<Node> nodes;
  std::unordered_set<Link> links;
};
