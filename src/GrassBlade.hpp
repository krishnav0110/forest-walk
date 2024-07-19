#ifndef _GRASS_H_
#define _GRASS_H_

#include <SFML/Graphics.hpp>
#include "PivotRod.hpp"

class GrassBlade {
private:
    std::vector<PivotRod*> blades;

public:
    glm::vec3 pos;
    GrassBlade(const glm::vec3 &pos, float length, float angle, float stiffness);
    void ApplyForce(const glm::vec2 &force);
    void Update(float dt);
    void AddVertices(std::vector<glm::vec3> &vertices, std::vector<float> &widths);
    ~GrassBlade();
};

#endif