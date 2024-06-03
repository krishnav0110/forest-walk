#include "Math.hpp"

float Math::Vec2::length(sf::Vector2f &vec) {
    return std::sqrtf(vec.x * vec.x + vec.y * vec.y);
}

float Math::Vec2::dot(sf::Vector2f &vec1, sf::Vector2f &vec2) {
    return {vec1.x * vec2.x + vec1.y * vec2.y};
}

float Math::Vec2::angleBetween(sf::Vector2f &vec1, sf::Vector2f &vec2) {
    float vec1_mag = Math::Vec2::length(vec1);
    float vec2_mag = Math::Vec2::length(vec2);
    if(vec1_mag == 0 || vec2_mag == 0) {
        return 0;
    }
    return std::acosf(Math::Vec2::dot(vec1, vec2) / (vec1_mag * vec2_mag));
}

sf::Vector2f Math::Vec2::normalize(sf::Vector2f &vec) {
    float k = 1 / Math::Vec2::length(vec);
    return sf::Vector2f(vec.x * k, vec.y * k);
}

sf::Vector2f Math::Vec2::rotateBy(sf::Vector2f &vec, float angle) {
    float mag = Math::Vec2::length(vec);
    if(mag == 0) {
        return {0, 0};
    }
    float targetAngle = std::acosf(vec.x / mag);
    if(vec.y < 0) {
        targetAngle = 2 * PI - targetAngle;
    }
    targetAngle += angle;
    return sf::Vector2f(mag * std::cosf(targetAngle), mag * std::sinf(targetAngle));
}