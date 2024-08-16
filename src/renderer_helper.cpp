#include "../include/renderer_helper.hpp"

void RendererHelper::drawCircleInterior(SDL_Renderer *renderer,
                                        const glm::vec2 &center,
                                        const float radius,
                                        const glm::tvec4<uint8_t> &color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  for (int32_t y = -radius; y <= radius; ++y) {
    for (int32_t x = -radius; x <= radius; ++x) {
      if (x * x + y * y <= radius * radius) {
        SDL_RenderDrawPoint(renderer, center.x + x, center.y + y);
      }
    }
  }
}

void RendererHelper::drawCircleOutline(SDL_Renderer *renderer,
                                       const glm::vec2 &center,
                                       const float radius,
                                       const glm::tvec4<uint8_t> &color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  float x = radius;
  float y = 0;
  float p = 1 - radius;
  SDL_RenderDrawPoint(renderer, center.x + x, center.y + y);
  SDL_RenderDrawPoint(renderer, center.x - x, center.y + y);
  SDL_RenderDrawPoint(renderer, center.x + y, center.y + x);
  SDL_RenderDrawPoint(renderer, center.x - y, center.y + x);
  while (x > y) {
    y += 1;
    if (p <= 0) {
      p += 2 * y + 1;
    } else {
      x -= 1;
      p += 2 * (y - x) + 1;
    }
    SDL_RenderDrawPoint(renderer, center.x + x, center.y + y);
    SDL_RenderDrawPoint(renderer, center.x - x, center.y + y);
    SDL_RenderDrawPoint(renderer, center.x + x, center.y - y);
    SDL_RenderDrawPoint(renderer, center.x - x, center.y - y);
    SDL_RenderDrawPoint(renderer, center.x + y, center.y + x);
    SDL_RenderDrawPoint(renderer, center.x - y, center.y + x);
    SDL_RenderDrawPoint(renderer, center.x + y, center.y - x);
    SDL_RenderDrawPoint(renderer, center.x - y, center.y - x);
  }
}

void RendererHelper::drawLine(SDL_Renderer *renderer, const glm::vec2 &start,
                              const glm::vec2 &end, const float thickness,
                              const glm::tvec4<uint8_t> &color) {
  const glm::vec2 direction = end - start;
  const float length = glm::length(direction);
  const glm::vec2 directionNorm = direction / length;
  const glm::vec2 perp = glm::vec2(-directionNorm.y, directionNorm.x);
  const glm::vec2 offset = perp * (thickness / 2.0f);
  const glm::vec2 points[4] = {
      glm::vec2(start.x + offset.x, start.y + offset.y),
      glm::vec2(end.x - offset.x, end.y + offset.y),
      glm::vec2(start.x - offset.x, start.y - offset.y),
      glm::vec2(end.x + offset.x, end.y - offset.y)};
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  for (uint8_t i = 0; i < 4; ++i) {
    for (uint8_t j = 0; j < 4; ++j) {
      SDL_RenderDrawLineF(renderer, points[i].x, points[i].y, points[j].x,
                          points[j].y);
    }
  }
}
