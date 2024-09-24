#pragma once

#include <cstdint>
#include <functional>

class Link {
public:
  Link(const uint32_t _idxNodeA, const uint32_t _idxNodeB);

  uint32_t getIdxA() const;
  uint32_t getIdxB() const;

  bool operator==(const Link &other) const;

private:
  const uint32_t idxNodeA;
  const uint32_t idxNodeB;
};

template <> struct std::hash<Link> {
  std::size_t operator()(const Link &k) const;
};
