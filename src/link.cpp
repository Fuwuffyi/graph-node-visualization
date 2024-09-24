#include "../include/link.hpp"
#include <cmath>

// idxNodeA < idxNodeB
Link::Link(const uint32_t _idxNodeA, const uint32_t _idxNodeB)
    : idxNodeA(std::min(_idxNodeA, _idxNodeB)),
      idxNodeB(std::max(_idxNodeA, _idxNodeB)) {}

uint32_t Link::getIdxA() const { return idxNodeA; }
uint32_t Link::getIdxB() const { return idxNodeB; }

bool Link::operator==(const Link &other) const {
  return (idxNodeA == other.idxNodeA && idxNodeB == other.idxNodeB) ||
         (idxNodeA == other.idxNodeB && idxNodeB == other.idxNodeA);
}
