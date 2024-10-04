#pragma once

#include <glm/glm.hpp>

class Node {
public:
  Node(const uint32_t id_, const float mass_, const glm::vec2 &position_,
       const glm::vec2 &velocity_ = glm::vec2(0.0f),
       const glm::vec2 &acceleration_ = glm::vec2(0.0f));
  Node(const uint32_t id_, const float mass_);
  Node(const uint32_t id_);

  void applyForce(const glm::vec2 &force);
  void update(const float velocityDamping,
              const float deltaTime); // Damping must be 0 .. 1

  const uint32_t &getId() const;
  const float &getMass() const;
  const glm::vec2 &getPosition() const;
  void setPosition(const glm::vec2 &pos);
  const glm::vec2 &getVelocity() const;
  const glm::vec2 &getAcceleration() const;

  bool operator==(const Node &other) const;

private:
  const uint32_t id;
  const float mass;
  glm::vec2 position;
  glm::vec2 velocity;
  glm::vec2 acceleration;
};
