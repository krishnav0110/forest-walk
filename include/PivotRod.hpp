#ifndef _PIVOTROD_H_
#define _PIVOTROD_H_

#include <SFML/Graphics.hpp>

struct PivotRod {
    PivotRod *parent = NULL;
    sf::Vector3f pos;
    sf::Vector3f endPos;
    float length = 0;
    float angle = 0;
    float ang_vel = 0;
    float ang_acc = 0;

    float restingAngle = 0;
    float stiffness = 0;
    float drag = 0;

    PivotRod(PivotRod* parent, float length, float restingAngle, float stiffness, float drag);

    void applyForce(sf::Vector2f &force);

    void update(float dt);
};

#endif