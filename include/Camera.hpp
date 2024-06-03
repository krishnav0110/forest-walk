#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/ext.hpp>

struct Plane {
    glm::vec3 point = {0.0f, 0.0f, 0.0f};
    glm::vec3 normal = {0.0f, 1.0f, 0.0f};

    Plane();
    Plane(glm::vec3 &point, glm::vec3 &normal);
    float distance(glm::vec3 &point);
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
    void update();
    bool circleWithinCamera(glm::vec3 &point, float radius);
    bool zWithinCamera(glm::vec3 &point);
    glm::mat4 viewMatrix();
    glm::mat4 projectionMatrix();
};

#endif