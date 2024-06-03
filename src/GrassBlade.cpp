#include "GrassBlade.hpp"
#include "Math.hpp"

GrassBlade::GrassBlade(sf::Vector3f &pos, float length, float angle, float stiffness) {
    this->pos = pos;
    float drag = 2.0f;

    PivotRod *p1 = new PivotRod(NULL, length, Math::HALF_PI + angle, stiffness, drag);
    length *= 0.75;
    PivotRod *p2 = new PivotRod(p1, length, angle, stiffness, drag);
    length *= 0.75;
    PivotRod *p3 = new PivotRod(p2, length, angle, stiffness, drag);
    blades.emplace_back(p1);
    blades.emplace_back(p2);
    blades.emplace_back(p3);
}

void GrassBlade::applyForce(sf::Vector2f &force) {
    for(PivotRod *rod: blades) {
        rod->applyForce(force);
    }
}

void GrassBlade::update(float dt) {
    blades[0]->pos = pos;
    for(PivotRod *rod: blades) {
        if(rod->parent != NULL) {
            rod->pos = rod->parent->endPos;
        }
        rod->update(dt);
    }
}

void GrassBlade::addVertices(std::vector<sf::Vector3f> &vertices, std::vector<float> &widths) {
    float width = 0.0015f;

    for(PivotRod *rod: blades) {
        vertices.emplace_back(rod->pos);
        widths.emplace_back(width);
        width -= 0.0005f;
        vertices.emplace_back(rod->endPos);
        widths.emplace_back(width);
        // Vertex v1{rod->pos - width, color};
        // Vertex v2{rod->pos + width, color};
        // width.x -= 0.0005f;
        // Vertex v3{rod->endPos - width, color};
        // Vertex v4{rod->endPos + width, color};
        
        // vertices.emplace_back(v1);
        // vertices.emplace_back(v2);
        // vertices.emplace_back(v3);
        // vertices.emplace_back(v3);
        // vertices.emplace_back(v2);
        // vertices.emplace_back(v4);
    }
}

GrassBlade::~GrassBlade() {
    for(PivotRod *rod: blades) {
        delete rod;
    }
    blades.clear();
}