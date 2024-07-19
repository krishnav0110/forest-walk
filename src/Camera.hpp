#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/ext.hpp>

struct Plane {
    glm::vec3 point = {0.0f, 0.0f, 0.0f};
    glm::vec3 normal = {0.0f, 1.0f, 0.0f};

    Plane();
    Plane(const glm::vec3 &point, const glm::vec3 &normal);
    float Distance(const glm::vec3 &point) const;
};

struct Camera {
    glm::vec3 pos;
    glm::vec3 up;
    glm::vec3 front;
    glm::vec3 right;
    float fov;
    float aspect;
    float zNear;
    float zFar;

    Plane topFace;
    Plane bottomFace;

    Plane rightFace;
    Plane leftFace;

    Camera(float fov, float aspect, float zNear, float zFar);
    void Update();

    bool CircleWithinCamera(const glm::vec3 &point, float radius) const;
    bool ZWithinCamera(const glm::vec3 &point) const;
    glm::mat4 ViewMatrix() const;
    glm::mat4 ProjectionMatrix() const;
};

#endif