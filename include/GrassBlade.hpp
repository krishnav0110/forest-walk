#ifndef _GRASS_H_
#define _GRASS_H_

#include <SFML/Graphics.hpp>
#include "PivotRod.hpp"

class GrassBlade {
private:
    std::vector<PivotRod*> blades;

public:
    sf::Vector3f pos;
    GrassBlade(sf::Vector3f &pos, float length, float angle, float stiffness);
    void applyForce(sf::Vector2f &force);
    void update(float dt);
    void addVertices(std::vector<sf::Vector3f> &vertices, std::vector<float> &widths);
    ~GrassBlade();
};

#endif