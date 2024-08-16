#pragma once

#include <glm/glm.hpp>
#include <string>

class Node {
public:
  Node(const std::string &name_, const float mass_, const glm::vec2 &position_,
       const glm::vec2 &velocity_ = glm::vec2(0.0f),
       const glm::vec2 &acceleration_ = glm::vec2(0.0f));
  Node(const std::string &name_, const float mass_);
  Node(const std::string &name_);

  void applyForce(const glm::vec2 &force);
  void update(const float velocityDamping,
              const float deltaTime); // Damping must be 0 .. 1

  const std::string &getName() const;
  const float &getMass() const;
  const glm::vec2 &getPosition() const;
  const glm::vec2 &getVelocity() const;
  const glm::vec2 &getAcceleration() const;

private:
  const std::string name;
  const float mass;
  glm::vec2 position;
  glm::vec2 velocity;
  glm::vec2 acceleration;
};
