#include "../include/simulation.hpp"

#include "../include/renderer_helper.hpp"

Simulation::Simulation(const std::vector<Node> &nodes_)
    : nodes(nodes_), links(){};
Simulation::Simulation() : Simulation(std::vector<Node>()){};

void Simulation::addNode(const Node &node) { nodes.push_back(node); }

void Simulation::addLink(const Node &nodeA, const Node &nodeB) {
  // TODO:
}

void Simulation::update(const float deltaTime) {
  // TODO: Add repulsion force, and center attraction force
  // TODO: Add link attraction forces

  // Update all the particles with the accumulated forces
  for (Node &node : nodes) {
    node.update(0.99f, deltaTime);
  }
}

void Simulation::render(SDL_Renderer *renderer) const {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (const Link_t &link : links) {
    const Node &nodeA = nodes[link.idxNodeA];
    const Node &nodeB = nodes[link.idxNodeB];
    RendererHelper::drawLine(renderer, nodeA.getPosition(), nodeB.getPosition(),
                             LINK_THICKNESS, LINK_COLOR);
  }
  for (const Node &node : nodes) {
    const float nodeRadius = NODE_SIZE_MULTIPLIER * node.getMass();
    RendererHelper::drawCircleInterior(renderer, node.getPosition(), nodeRadius,
                                       NODE_FILL);
    RendererHelper::drawCircleOutline(renderer, node.getPosition(), nodeRadius,
                                      NODE_OUTLINE);
  }
}
