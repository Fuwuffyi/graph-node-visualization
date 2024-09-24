#pragma once

#include "simulation.hpp"
#include <string>

class FileParser {
public:
  FileParser(const std::string &filePath);

  const std::set<Simulation::Link_t> &getLinks();

private:
  std::set<Simulation::Link_t> links;
};
