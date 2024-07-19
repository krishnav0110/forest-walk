#ifndef _LENSFLARE_H_
#define _LENSFLARE_H_

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include "core/Model.hpp"

struct LensFlare {
    glm::vec2 windowSize;
    Model model;
    sf::Texture flareTex;
    float alpha;

    LensFlare(const glm::ivec2 &windowSize);
    void Update(const glm::vec2 &sunPos);
};

#endif