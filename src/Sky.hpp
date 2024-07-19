#ifndef _SKY_H_
#define _SKY_H_

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include "core/Model.hpp"

struct Sky {
    glm::vec2 sunPos;
    Model sunModel;
    Model model;
    sf::Texture sunTex;
    Sky(const glm::ivec2 &windowSize);
};

#endif