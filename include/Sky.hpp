#ifndef _SKY_H_
#define _SKY_H_

#include <SFML/Graphics.hpp>
#include "Model.hpp"

struct Sky {
    sf::Vector2f sunPos;
    Model sunModel;
    Model model;
    sf::Texture sunTex;
    Sky();
};

#endif