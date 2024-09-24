#include "../include/simulation.hpp"

#include "../include/renderer_helper.hpp"

#include <SDL2/SDL_ttf.h>
#include <filesystem>

Simulation::Simulation(const float width_, const float height_,
                       const std::vector<Node> &nodes_)
    : dimensions(width_, height_), translation(dimensions / 2.0f),
      nodes(nodes_), links(){};
Simulation::Simulation(const float width_, const float height_)
    : Simulation(width_, height_, std::vector<Node>()){};

void Simulation::addNode(const Node &node) { nodes.push_back(node); }

void Simulation::addLink(const uint32_t indexA, const uint32_t indexB) {
  links.insert(Link{indexA, indexB});
}

void Simulation::addLinks(const std::unordered_set<Link> &linksToAdd) {
  for (const Link &link : linksToAdd) {
    this->links.insert(link);
  }
}

void Simulation::update(const float deltaTime) {
  for (Node &node : nodes) {
    // Add center gravity force to all nodes
    const glm::vec2 centerAttractionForce =
        -(node.getPosition() / translation) * CENTER_ATTRACTION_FORCE_MULT;
    node.applyForce(centerAttractionForce);
    // Add all nodes repulsion force
    for (Node &other : nodes) {
      if (&other != &node) {
        // Calculate distance and direction
        float distance = glm::distance(other.getPosition(), node.getPosition());
        if (distance < 0.001f) {
          distance = 0.001f;
        }
        const glm::vec2 directionVector =
            -glm::normalize(other.getPosition() - node.getPosition());
        // Calculate the force, using the inverse of distance (stronger force
        // when close), multiplied by half cause newton
        node.applyForce(directionVector * (1.0f / distance) *
                        REPULSION_FORCE_MULT * 0.5f);
      }
    }
  }
  for (const Link &link : links) {
    // Get the two nodes linked together
    Node &nodeA = nodes[link.getIdxA()];
    Node &nodeB = nodes[link.getIdxB()];
    // Calculate distance and direction
    const float distance =
        glm::distance(nodeB.getPosition(), nodeA.getPosition());
    if (distance > ATTRACTION_DISTANCE_TRESHOLD) {
      const glm::vec2 directionVector =
          glm::normalize(nodeB.getPosition() - nodeA.getPosition());
      // Calculate the force, using f(x) = x^2 * (1/s) (stronger force
      // when far), multiplied by half cause newton
      nodeA.applyForce(directionVector *
                       (std::powf(distance - ATTRACTION_DISTANCE_TRESHOLD, 2) *
                        (1 / (std::powf(glm::length(translation), 2)))) *
                       ATTRACTION_FORCE_MULT * 0.5f);
      nodeB.applyForce(-directionVector *
                       (std::powf(distance - ATTRACTION_DISTANCE_TRESHOLD, 2) *
                        (1 / (std::powf(glm::length(translation), 2)))) *
                       ATTRACTION_FORCE_MULT * 0.5f);
    }
  }
  // Update all the particles with the accumulated forces
  for (Node &node : nodes) {
    node.update(VELOCITY_DAMPING, deltaTime);
  }
}

void Simulation::render(SDL_Renderer *renderer,
                        const Node *selectedNode) const {
  glm::tvec4<uint8_t> linkColor = LINK_COLOR;
  glm::tvec4<uint8_t> nodeFill = NODE_FILL;
  glm::tvec4<uint8_t> nodeOutline = NODE_OUTLINE;
  glm::tvec4<uint8_t> textColor = TEXT_COLOR;
  if (selectedNode != nullptr) {
    linkColor.a = 5;
    nodeFill.a = 40;
    nodeOutline.a = 40;
    textColor.a = 40;
  }
  for (const Link &link : links) {
    const Node &nodeA = nodes[link.getIdxA()];
    const Node &nodeB = nodes[link.getIdxB()];
    RendererHelper::drawLine(
        renderer, nodeA.getPosition() + translation,
        nodeB.getPosition() + translation, LINK_THICKNESS,
        selectedNode != nullptr &&
                ((nodeA == *selectedNode) || (nodeB == *selectedNode))
            ? LINK_COLOR
            : linkColor);
  }
  for (uint32_t i = 0; i < nodes.size(); ++i) {
    const Node &node = nodes[i];
    const float nodeRadius = NODE_SIZE_MULTIPLIER * node.getMass();
    const glm::vec2 currentPos = node.getPosition() + translation;
    RendererHelper::drawCircleInterior(
        renderer, currentPos, nodeRadius,
        selectedNode != nullptr && (node == *selectedNode) ? NODE_FILL
                                                           : nodeFill);
    RendererHelper::drawCircleOutline(
        renderer, currentPos, nodeRadius,
        selectedNode != nullptr && (node == *selectedNode) ? NODE_OUTLINE
                                                           : nodeOutline);
    static TTF_Font *font = TTF_OpenFont(
        (std::filesystem::current_path().generic_string() + "/comicsans.ttf")
            .c_str(),
        64);
    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(
        font, std::to_string(i + 1).c_str(),
        {textColor.r, textColor.g, textColor.b, textColor.a});
    SDL_Texture *message =
        SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    const SDL_Rect Message_rect = SDL_Rect{
        int32_t(currentPos.x - nodeRadius), int32_t(currentPos.y - nodeRadius),
        int32_t(nodeRadius * 2.0f), int32_t(nodeRadius * 2.0f)};
    SDL_RenderCopy(renderer, message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
  }
}

const std::vector<Node> &Simulation::getNodes() const { return nodes; }
std::vector<Node> &Simulation::getEditableNodes() { return nodes; }
const std::unordered_set<Link> &Simulation::getLinks() const { return links; }
