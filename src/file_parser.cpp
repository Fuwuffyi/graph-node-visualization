#include "../include/file_parser.hpp"
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

FileParser::FileParser(const std::string &filePath) {
  std::ifstream file(filePath);
  if (!file.is_open()) {
    throw std::runtime_error("No file found at: " + filePath);
  }
  // Split all lines
  std::string line;
  std::map<uint8_t, std::vector<uint8_t>> collisionMap;
  while (getline(file, line)) {
    std::stringstream ss(line);
    // Get ID
    std::string str_id;
    getline(ss, str_id, '\t');
    const uint8_t id = static_cast<uint8_t>(std::stoi(str_id) - 1);
    // Get connections string
    std::string connections;
    getline(ss, connections);
    // Streamify that string
    std::stringstream conn_stream(connections);
    std::string conn_str;
    // Get all connections from string
    std::vector<uint8_t> connection_list;
    while (getline(conn_stream, conn_str, ' ')) {
      const uint8_t connection = static_cast<uint8_t>(std::stoi(conn_str) - 1);
      if (id != connection) {
        links.insert(Simulation::Link_t{id, connection});
      }
    }
  }
  file.close();
}

const std::set<Simulation::Link_t> &FileParser::getLinks() { return links; }
