#include "../include/node.hpp"

Node::Node(const std::string &name_, const float mass_,
           const glm::vec2 &position_, const glm::vec2 &velocity_,
           const glm::vec2 &acceleration_)
    : name(name_), mass(mass_), position(position_), velocity(velocity_),
      acceleration(acceleration_) {}

Node::Node(const std::string &name_, const float mass_)
    : Node(name_, mass_, glm::vec2(0.0f)) {}

Node::Node(const std::string &name_) : Node(name_, 1.0f) {}

void Node::applyForce(const glm::vec2 &force) { acceleration += force / mass; }

void Node::update(const float velocityDamping, const float deltaTime) {
  velocity += acceleration * deltaTime;
  velocity *= velocityDamping;
  position += velocity * deltaTime;
  acceleration = glm::vec2(0.0f);
}

const std::string &Node::getName() const { return name; }
const float &Node::getMass() const { return mass; }
const glm::vec2 &Node::getPosition() const { return position; }
const glm::vec2 &Node::getVelocity() const { return velocity; }
const glm::vec2 &Node::getAcceleration() const { return acceleration; }
