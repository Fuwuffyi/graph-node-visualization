#include "../include/renderer_helper.hpp"

void RendererHelper::drawPixel(SDL_Renderer *renderer, const float x,
                               const float y) {
  const int32_t ix = static_cast<int32_t>(x + 0.5f);
  const int32_t iy = static_cast<int32_t>(y + 0.5f);
  SDL_RenderDrawPoint(renderer, ix, iy);
}

void RendererHelper::drawCircle(SDL_Renderer *renderer, const glm::vec2 &center,
                                const float radius) {
  float x = radius;
  float y = 0;
  float p = 1 - radius; // Decision parameter
  // Initial point on the perimeter of the circle
  drawPixel(renderer, center.x + x, center.y + y);
  drawPixel(renderer, center.x - x, center.y + y);
  drawPixel(renderer, center.x + y, center.y + x);
  drawPixel(renderer, center.x - y, center.y + x);
  // Draw the circle using the symmetry of the eight octants
  while (x > y) {
    y += 1;
    if (p <= 0) {
      p += 2 * y + 1;
    } else {
      x -= 1;
      p += 2 * (y - x) + 1;
    }
    // Draw points for each octant
    drawPixel(renderer, center.x + x, center.y + y);
    drawPixel(renderer, center.x - x, center.y + y);
    drawPixel(renderer, center.x + x, center.y - y);
    drawPixel(renderer, center.x - x, center.y - y);
    drawPixel(renderer, center.x + y, center.y + x);
    drawPixel(renderer, center.x - y, center.y + x);
    drawPixel(renderer, center.x + y, center.y - x);
    drawPixel(renderer, center.x - y, center.y - x);
  }
}

void drawLine(SDL_Renderer *renderer, const glm::vec2 &start,
              const glm::vec2 &end, float thickness) {
  const glm::vec2 direction = end - start;
  const float length = glm::length(direction);
  const glm::vec2 directionNorm = direction / length;
  const glm::vec2 perp = glm::vec2(-directionNorm.y, directionNorm.x);
  const glm::vec2 offset = perp * (thickness / 2.0f);
  const SDL_FPoint points[4] = {{start.x + offset.x, start.y + offset.y},
                                {start.x - offset.x, start.y - offset.y},
                                {end.x - offset.x, end.y - offset.y},
                                {end.x + offset.x, end.y + offset.y}};
  SDL_RenderDrawLinesF(renderer, points, 4);
}
