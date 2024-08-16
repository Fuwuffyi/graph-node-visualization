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
  void addLink(/* TODO: */);

  void update(const float deltaTime);
  void render(SDL_Renderer *renderer) const;

private:
  std::vector<Node> nodes;
  std::vector<Link_t> links;
};
