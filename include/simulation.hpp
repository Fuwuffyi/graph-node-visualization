#pragma once

#include "node.hpp"
#include <SDL2/SDL.h>
#include <set>
#include <vector>

class Simulation {
private:
  typedef struct Link {
    const uint32_t idxNodeA;
    const uint32_t idxNodeB;

    bool operator<(const Link &other) const {
      if (idxNodeA != other.idxNodeA) {
        return idxNodeA < other.idxNodeA;
      }
      return idxNodeB < other.idxNodeB;
    }
  } Link_t;

public:
  Simulation(const float width_, const float height_,
             const std::vector<Node> &nodes_);
  Simulation(const float width_, const float height_);

  void addNode(const Node &node);
  void addLink(const uint32_t indexA, const uint32_t indexB);

  void update(const float deltaTime);
  void render(SDL_Renderer *renderer) const;

  const std::vector<Node> &getNodes() const;
  const std::set<Link_t> &getLinks() const;

private:
  // Simulation visualization parameters
  static constexpr glm::tvec4<uint8_t> LINK_COLOR =
      glm::tvec4<uint8_t>(44, 44, 44, 255); // The node's link line color
  static constexpr glm::tvec4<uint8_t> NODE_OUTLINE =
      glm::tvec4<uint8_t>(225, 225, 225, 100); // Node's outline color in RGBA
  static constexpr glm::tvec4<uint8_t> NODE_FILL =
      glm::tvec4<uint8_t>(179, 179, 179, 255);  // Node's inner color in RGBA
  static constexpr float LINK_THICKNESS = 8.0f; // Thickness of the link line
  static constexpr float NODE_SIZE_MULTIPLIER =
      12.0f; // Node's radius multiplier
             // Simulation physics parameters
  static constexpr float VELOCITY_DAMPING =
      0.9f; // Multiplies the velocity every frame (0.0f - 1.0f)
  static constexpr float CENTER_ATTRACTION_FORCE_MULT =
      200.0f; // Multiplies the center attraction force
  static constexpr float REPULSION_FORCE_MULT = 800.0f;
  static constexpr float ATTRACTION_FORCE_MULT = 2000.0f;
  static constexpr float ATTRACTION_DISTANCE_TRESHOLD =
      80.0f; // Maximum distance at which there is no attraction

private:
  // Actual needed variables
  const glm::vec2 dimensions;
  const glm::vec2 translation;
  std::vector<Node> nodes;
  std::set<Link_t> links;
};
