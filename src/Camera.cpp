#include "Camera.hpp"

Plane::Plane() {
    this->point = {0.0f, 0.0f, 0.0f};
    this->normal = {0.0f, 1.0f, 0.0f};
}
Plane::Plane(const glm::vec3 &point, const glm::vec3 &normal) {
    this->point = point;
    this->normal = normal;
}

float Plane::Distance(const glm::vec3 &point) const {
    return glm::dot(point - this->point, normal);
}

Camera::Camera(float fov, float aspect, float zNear, float zFar) {
    this->pos = {0.0f, 0.065f, 0.0f};
    this->up = {0.0f, 1.0f, 0.0f};
    this->front = {0.0f, sinf(0.24f), -cosf(0.24f)};
    this->right = {1.0f, 0.0f, 0.0f};
    this->fov = fov;
    this->aspect = aspect;
    this->zNear = zNear;
    this->zFar = zFar;
}

void Camera::Update() {
    float halfVSide = zFar * tanf(fov);
    float halfHSide = halfVSide * aspect;
    glm::vec3 frontMultFar = zFar * front;

    rightFace = {pos, glm::normalize(glm::cross(frontMultFar + right * halfHSide - pos, up))};
    leftFace = {pos, glm::normalize(glm::cross(up, frontMultFar - right * halfHSide - pos))};
    topFace = {pos, glm::normalize(glm::cross(right, frontMultFar + up * halfVSide - pos))};
    bottomFace = {pos, glm::normalize(glm::cross(frontMultFar - up * halfVSide - pos, right))};
}

bool Camera::CircleWithinCamera(const glm::vec3 &point, float radius) const {
    float pointZ = glm::dot(point - pos, front);

    if(pointZ < zNear || pointZ - 1.2f > zFar) {
        return false;
    }
    if(rightFace.Distance(point) < radius) {
        return true;
    }
    else if(leftFace.Distance(point) < radius) {
        return true;
    }
    else if(bottomFace.Distance(point) < radius) {
        return true;
    }
    else if(topFace.Distance(point) < radius) {
        return true;
    }
    return false;
}

bool Camera::ZWithinCamera(const glm::vec3 &point) const {
    float pointZ = glm::dot(point - pos, front);

    if(pointZ < zNear || pointZ > zFar) {
        return false;
    }
    return true;
}

glm::mat4 Camera::ViewMatrix() const {
    return glm::lookAt(pos, pos + front, up);
}

glm::mat4 Camera::ProjectionMatrix() const {
    glm::mat4 projectionMatrix = glm::mat4(1.0f);
    return glm::perspective(fov, aspect, zNear, zFar);
}