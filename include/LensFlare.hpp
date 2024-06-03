#ifndef _LENSFLARE_H_
#define _LENSFLARE_H_

#include <SFML/Graphics.hpp>
#include "Model.hpp"

struct LensFlare {
    Model model;
    sf::Texture flareTex;
    float alpha;

    LensFlare();
    void update(sf::Vector2f &sunPos);
};

#endif