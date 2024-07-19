#include "PivotRod.hpp"
#include "util/MathUtil.hpp"

PivotRod::PivotRod(PivotRod* parent, float length, float restingAngle, float stiffness, float drag) {
    this->parent = parent;
    this->pos = {0.0f, 0.0f, 0.0f};
    this->endPos = {0.0f, 0.0f, 0.0f};
    this->length = length;
    this->angle = restingAngle;
    this->ang_vel = 0;
    this->ang_acc = 0;
    this->restingAngle = restingAngle;
    this->stiffness = stiffness;
    this->drag = drag;
}

void PivotRod::ApplyForce(const glm::vec2 &force) {
    glm::vec3 dir3 = endPos - pos;
    glm::vec2 dir = glm::vec2(dir3.x, dir3.y) ;
    float angle = MathUtil::Vec2::AngleBetween(force, dir);
    float torque_dir = dir.x * force.y - dir.y * force.x;
    float torque = MathUtil::Vec2::Length(force) * sinf(angle);
    ang_acc = torque_dir >= 0 ? torque : -torque;
}

void PivotRod::Update(float dt) {
    float d_angle = this->angle - restingAngle;
    float force = -stiffness * d_angle;
    ang_acc += force;

    float damp_force = drag * ang_vel;
    ang_acc -= damp_force;
    
    ang_vel += ang_acc * dt;
    ang_acc = 0;
    this->angle += ang_vel * dt;

    float angle = this->angle;
    PivotRod *parent = this->parent;

    while(parent != NULL) {
        angle += parent->angle;
        parent = parent->parent;
    }
    this->endPos = {pos.x + length * cosf(angle), pos.y + length * sinf(angle), pos.z};
}