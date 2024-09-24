#include "../include/node.hpp"

Node::Node(const uint32_t id_, const float mass_, const glm::vec2 &position_,
           const glm::vec2 &velocity_, const glm::vec2 &acceleration_)
    : id(id_), mass(mass_), position(position_), velocity(velocity_),
      acceleration(acceleration_) {}

Node::Node(const uint32_t id_, const float mass_)
    : Node(id_, mass_, glm::vec2(0.0f)) {}

Node::Node(const uint32_t id_) : Node(id_, 1.0f) {}

void Node::applyForce(const glm::vec2 &force) { acceleration += force / mass; }

void Node::update(const float velocityDamping, const float deltaTime) {
  velocity += acceleration * deltaTime;
  velocity *= velocityDamping;
  position += velocity;
  acceleration = glm::vec2(0.0f);
}

const float &Node::getMass() const { return mass; }
const glm::vec2 &Node::getPosition() const { return position; }
void Node::setPosition(const glm::vec2 &pos) { position = pos; };
const glm::vec2 &Node::getVelocity() const { return velocity; }
const glm::vec2 &Node::getAcceleration() const { return acceleration; }

bool Node::operator==(const Node &other) const { return id == other.id; }
