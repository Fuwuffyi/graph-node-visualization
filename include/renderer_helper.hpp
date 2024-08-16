#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

namespace RendererHelper {

void drawCircleInterior(SDL_Renderer *renderer, const glm::vec2 &center,
                        const float radius, const glm::tvec4<uint8_t> &color);

void drawCircleOutline(SDL_Renderer *renderer, const glm::vec2 &center,
                       const float radius, const glm::tvec4<uint8_t> &color);

void drawLine(SDL_Renderer *renderer, const glm::vec2 &start,
              const glm::vec2 &end, const float thickness,
              const glm::tvec4<uint8_t> &color);

} // namespace RendererHelper
