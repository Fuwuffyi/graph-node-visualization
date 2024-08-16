#include "../include/simulation.hpp"

#include "../include/renderer_helper.hpp"

Simulation::Simulation(const float width_, const float height_,
                       const std::vector<Node> &nodes_)
    : dimensions(width_, height_), translation(dimensions / 2.0f),
      nodes(nodes_), links(){};
Simulation::Simulation(const float width_, const float height_)
    : Simulation(width_, height_, std::vector<Node>()){};

void Simulation::addNode(const Node &node) { nodes.push_back(node); }

void Simulation::addLink(const Node &nodeA, const Node &nodeB) {
  // TODO:
}

void Simulation::update(const float deltaTime) {
  for (Node &node : nodes) {
    const glm::vec2 centerAttractionForce =
        -(node.getPosition() / translation) * CENTER_ATTRACTION_FORCE_MULT;
    node.applyForce(centerAttractionForce);
    for (Node &other : nodes) {
      // TODO: add repulsion force
    }
  }
  // TODO: Add link attraction forces

  // Update all the particles with the accumulated forces
  for (Node &node : nodes) {
    node.update(VELOCITY_DAMPING, deltaTime);
  }
}

void Simulation::render(SDL_Renderer *renderer) const {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (const Link_t &link : links) {
    const Node &nodeA = nodes[link.idxNodeA];
    const Node &nodeB = nodes[link.idxNodeB];
    RendererHelper::drawLine(renderer, nodeA.getPosition() + translation,
                             nodeB.getPosition(), LINK_THICKNESS, LINK_COLOR);
  }
  for (const Node &node : nodes) {
    const float nodeRadius = NODE_SIZE_MULTIPLIER * node.getMass();
    RendererHelper::drawCircleInterior(
        renderer, node.getPosition() + translation, nodeRadius, NODE_FILL);
    RendererHelper::drawCircleOutline(
        renderer, node.getPosition() + translation, nodeRadius, NODE_OUTLINE);
  }
}
