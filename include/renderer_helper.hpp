#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

namespace RendererHelper {

void drawPixel(SDL_Renderer *renderer, const float x, const float y);

void drawCircle(SDL_Renderer *renderer, const glm::vec2 &center,
                const float radius);

void drawLine(SDL_Renderer *renderer, const glm::vec2 &start,
              const glm::vec2 &end, float thickness);

} // namespace RendererHelper
