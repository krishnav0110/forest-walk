#ifndef _MATH_H_
#define _MATH_H_

#include <SFML/Graphics.hpp>

namespace Math {

const float PI = 3.14159f;
const float HALF_PI = 1.57079f;
const float PI_2 = 6.28318f;

namespace Vec2 {
    float length(sf::Vector2f &vec);
    float dot(sf::Vector2f &vec1, sf::Vector2f &vec2);
    float angleBetween(sf::Vector2f &vec1, sf::Vector2f &vec2);
    sf::Vector2f normalize(sf::Vector2f& vec);
    sf::Vector2f rotateBy(sf::Vector2f& vec, float angle);
}
}

#endif