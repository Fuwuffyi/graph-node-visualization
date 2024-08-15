#include "../include/node.hpp"

Node::Node(const std::string &name_, const float mass_)
    : name(name_), mass(mass_), position(0.0f), velocity(0.0f),
      acceleration(0.0f) {}

Node::Node(const std::string &name_) : Node(name_, 1.0f) {}

void Node::applyForce(const glm::vec2 &force, const float deltaTime) {
  acceleration += force / mass * deltaTime;
}

void Node::update(const float velocityDamping) {
  velocity += acceleration;
  velocity *= velocityDamping;
  position += velocity;
  acceleration = glm::vec2(0.0f);
}

const std::string &Node::getName() const { return name; }
const float &Node::getMass() const { return mass; }
const glm::vec2 &Node::getPosition() const { return position; }
const glm::vec2 &Node::getVelocity() const { return velocity; }
const glm::vec2 &Node::getAcceleration() const { return acceleration; }
