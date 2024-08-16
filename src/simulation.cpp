#include "../include/simulation.hpp"

Simulation::Simulation(const std::vector<Node> &nodes_)
    : nodes(nodes_), links(){};
Simulation::Simulation() : Simulation(std::vector<Node>()){};

void Simulation::addNode(const Node &node) {
  // TODO:
}

void Simulation::addLink(/* TODO: */) {
  // TODO:
}

void Simulation::update(const float deltaTime) {
  // TODO:
}

void Simulation::render(SDL_Renderer *renderer) const {
  // TODO:
}
