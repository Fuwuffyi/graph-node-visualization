#include "../include/link.hpp"

Link::Link(const Node &nodeA_, const Node &nodeB_)
    : nodeA(nodeA_), nodeB(nodeB_) {}

const Node &Link::getNodeA() const { return nodeA; }

const Node &Link::getNodeB() const { return nodeB; }
