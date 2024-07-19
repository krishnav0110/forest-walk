#ifndef _PIVOTROD_H_
#define _PIVOTROD_H_

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

struct PivotRod {
    PivotRod *parent = NULL;
    glm::vec3 pos;
    glm::vec3 endPos;
    float length = 0;
    float angle = 0;
    float ang_vel = 0;
    float ang_acc = 0;

    float restingAngle = 0;
    float stiffness = 0;
    float drag = 0;

    PivotRod(PivotRod* parent, float length, float restingAngle, float stiffness, float drag);

    void ApplyForce(const glm::vec2 &force);
    void Update(float dt);
};

#endif