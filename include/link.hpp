#pragma once

#include "node.hpp"
#include <memory>

class Link {
public:
  Link(const std::shared_ptr<Node> &nodeA_,
       const std::shared_ptr<Node> &nodeB_);

  const std::shared_ptr<Node> &getNodeA() const;
  const std::shared_ptr<Node> &getNodeB() const;

private:
  const std::shared_ptr<Node> nodeA;
  const std::shared_ptr<Node> nodeB;
};
