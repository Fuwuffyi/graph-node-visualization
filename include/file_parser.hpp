#pragma once

#include "link.hpp"
#include <string>
#include <unordered_set>

class FileParser {
public:
  FileParser(const std::string &filePath);

  const std::unordered_set<Link> &getLinks();

private:
  std::unordered_set<Link> links;
};
