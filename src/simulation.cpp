#include "../include/simulation.hpp"

#include "../include/renderer_helper.hpp"

Simulation::Simulation(const float width_, const float height_,
                       const std::vector<Node> &nodes_)
    : dimensions(width_, height_), translation(dimensions / 2.0f),
      nodes(nodes_), links(){};
Simulation::Simulation(const float width_, const float height_)
    : Simulation(width_, height_, std::vector<Node>()){};

void Simulation::addNode(const Node &node) { nodes.push_back(node); }

void Simulation::addLink(const uint32_t indexA, const uint32_t indexB) {
  links.emplace_back(indexA, indexB);
}

void Simulation::update(const float deltaTime) {
  for (Node &node : nodes) {
    // Add center gravity force to all nodes
    const glm::vec2 centerAttractionForce =
        -(node.getPosition() / translation) * CENTER_ATTRACTION_FORCE_MULT;
    node.applyForce(centerAttractionForce);
    // Add all nodes repulsion force
    for (Node &other : nodes) {
      if (&other != &node) {
        // Calculate distance and direction
        // TODO: Add distance treshold
        const float distance =
            glm::distance(other.getPosition(), node.getPosition());
        const glm::vec2 directionVector =
            -glm::normalize(other.getPosition() - node.getPosition());
        // Calculate the force, using the inverse of distance (stronger force
        // when close), multiplied by half cause newton
        node.applyForce(directionVector * (1.0f / distance) *
                        REPULSION_FORCE_MULT * 0.5f);
      }
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
                             nodeB.getPosition() + translation, LINK_THICKNESS,
                             LINK_COLOR);
  }
  for (const Node &node : nodes) {
    const float nodeRadius = NODE_SIZE_MULTIPLIER * node.getMass();
    RendererHelper::drawCircleInterior(
        renderer, node.getPosition() + translation, nodeRadius, NODE_FILL);
    RendererHelper::drawCircleOutline(
        renderer, node.getPosition() + translation, nodeRadius, NODE_OUTLINE);
  }
}

const std::vector<Node> &Simulation::getNodes() const { return nodes; }
const std::vector<Simulation::Link_t> &Simulation::getLinks() const {
  return links;
}
