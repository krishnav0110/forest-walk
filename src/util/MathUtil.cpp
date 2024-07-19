#include "MathUtil.hpp"

float MathUtil::Vec2::Length(const glm::vec2 &vec) {
    return std::sqrtf(vec.x * vec.x + vec.y * vec.y);
}

float MathUtil::Vec2::Dot(const glm::vec2 &vec1, const glm::vec2 &vec2) {
    return {vec1.x * vec2.x + vec1.y * vec2.y};
}

float MathUtil::Vec2::AngleBetween(const glm::vec2 &vec1, const glm::vec2 &vec2) {
    float vec1_mag = MathUtil::Vec2::Length(vec1);
    float vec2_mag = MathUtil::Vec2::Length(vec2);
    if(vec1_mag == 0 || vec2_mag == 0) {
        return 0;
    }
    return std::acosf(MathUtil::Vec2::Dot(vec1, vec2) / (vec1_mag * vec2_mag));
}

glm::vec2 MathUtil::Vec2::Normalize(const glm::vec2 &vec) {
    float k = 1 / MathUtil::Vec2::Length(vec);
    return glm::vec2(vec.x * k, vec.y * k);
}

glm::vec2 MathUtil::Vec2::RotateBy(const glm::vec2 &vec, float angle) {
    float mag = MathUtil::Vec2::Length(vec);
    if(mag == 0) {
        return {0, 0};
    }
    float targetAngle = std::acosf(vec.x / mag);
    if(vec.y < 0) {
        targetAngle = 2 * PI - targetAngle;
    }
    targetAngle += angle;
    return glm::vec2(mag * std::cosf(targetAngle), mag * std::sinf(targetAngle));
}