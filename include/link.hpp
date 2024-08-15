#pragma once

#include "node.hpp"

class Link {
public:
  Link(const Node &nodeA_, const Node &nodeB_);

  const Node &getNodeA() const;
  const Node &getNodeB() const;

private:
  const Node &nodeA;
  const Node &nodeB;
};
