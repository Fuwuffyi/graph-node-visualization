#include "../include/link.hpp"

Link::Link(const std::shared_ptr<Node> &nodeA_,
           const std::shared_ptr<Node> &nodeB_)
    : nodeA(nodeA_), nodeB(nodeB_) {}

const std::shared_ptr<Node> &Link::getNodeA() const { return nodeA; }

const std::shared_ptr<Node> &Link::getNodeB() const { return nodeB; }
