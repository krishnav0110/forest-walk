#include "GrassBlade.hpp"
#include "util/MathUtil.hpp"

GrassBlade::GrassBlade(const glm::vec3 &pos, float length, float angle, float stiffness) {
    this->pos = pos;
    float drag = 2.0f;

    PivotRod *p1 = new PivotRod(NULL, length, MathUtil::HALF_PI + angle, stiffness, drag);
    length *= 0.75;
    PivotRod *p2 = new PivotRod(p1, length, angle, stiffness, drag);
    length *= 0.75;
    PivotRod *p3 = new PivotRod(p2, length, angle, stiffness, drag);
    blades.emplace_back(p1);
    blades.emplace_back(p2);
    blades.emplace_back(p3);
}

void GrassBlade::ApplyForce(const glm::vec2 &force) {
    for(PivotRod *rod: blades) {
        rod->ApplyForce(force);
    }
}

void GrassBlade::Update(float dt) {
    blades[0]->pos = pos;
    for(PivotRod *rod: blades) {
        if(rod->parent != NULL) {
            rod->pos = rod->parent->endPos;
        }
        rod->Update(dt);
    }
}

void GrassBlade::AddVertices(std::vector<glm::vec3> &vertices, std::vector<float> &widths) {
    float width = 0.0015f;

    for(PivotRod *rod: blades) {
        vertices.emplace_back(rod->pos);
        widths.emplace_back(width);
        width -= 0.0005f;
        vertices.emplace_back(rod->endPos);
        widths.emplace_back(width);
    }
}

GrassBlade::~GrassBlade() {
    for(PivotRod *rod: blades) {
        delete rod;
    }
    blades.clear();
}