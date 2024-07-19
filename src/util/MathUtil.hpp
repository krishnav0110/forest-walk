#ifndef _MATH_H_
#define _MATH_H_

#include <glm/glm.hpp>

namespace MathUtil {

const float PI = 3.14159f;
const float HALF_PI = PI * 0.5f;
const float PI_2 = PI * 2.0f;

namespace Vec2 {
    float Length(const glm::vec2 &vec);
    float Dot(const glm::vec2 &vec1, const glm::vec2 &vec2);
    float AngleBetween(const glm::vec2 &vec1, const glm::vec2 &vec2);
    glm::vec2 Normalize(const glm::vec2& vec);
    glm::vec2 RotateBy(const glm::vec2& vec, float angle);
}
}

#endif