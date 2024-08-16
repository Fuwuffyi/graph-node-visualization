#include "../include/renderer_helper.hpp"
#include <SDL2/SDL_render.h>

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
  const glm::vec2 deltaPos = end - start;
  const float length = glm::length(deltaPos);
  const glm::vec2 unitDelta = deltaPos / length;
  const glm::vec2 perp = glm::vec2(-unitDelta.y, unitDelta.x) * (thickness / 2);
  const glm::vec2 points[4] = {start + perp, start - perp, end - perp,
                               end + perp};
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderDrawLine(renderer, points[0].x, points[0].y, points[1].x,
                     points[1].y);
  SDL_RenderDrawLine(renderer, points[1].x, points[1].y, points[2].x,
                     points[2].y);
  SDL_RenderDrawLine(renderer, points[2].x, points[2].y, points[3].x,
                     points[3].y);
  SDL_RenderDrawLine(renderer, points[3].x, points[3].y, points[0].x,
                     points[0].y);
}
