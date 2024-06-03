#include "LensFlare.hpp"
#include "settings.h"

LensFlare::LensFlare() {
    std::vector<sf::Vector2f> positions;
    std::vector<sf::Vector2f> texCoords;

    model.vao.Bind();
    model.load(positions.size(), GL_TRIANGLES);
    model.loadVBO(std::string("positions"), 66 * sizeof(sf::Vector2f), 2, sizeof(sf::Vector2f), positions.data(), GL_DYNAMIC_DRAW);
    model.loadVBO(std::string("texCoords"), 66 * sizeof(sf::Vector2f), 2, sizeof(sf::Vector2f), texCoords.data(), GL_DYNAMIC_DRAW);
    model.vao.Unbind();

    flareTex.loadFromFile("res/tex/flare.png");
}

void LensFlare::update(sf::Vector2f &sunPos) {
    sf::Vector2f sunToCenter(-sunPos.x, -sunPos.y);
    float length = sqrtf(sunToCenter.x * sunToCenter.x + sunToCenter.y * sunToCenter.y);
    this->alpha = 1.0f - length / 0.62f;

    sf::Vector2f flarePosInc(sunToCenter / 6.0f);
    int texIndex[11] = {5, 3, 1, 6, 2, 4, 6, 2, 4, 3, 7};
    float scale[11] = {0.125f, 0.23f, 0.05f, 0.025f, 0.0015f, 0.0175f, 0.1f, 0.0175f, 0.075f, 0.4f, 0.6f};
    float radiusY = 0.6f;
    float radiusX = radiusY / WINDOW_WIDTH * WINDOW_HEIGHT;

    std::vector<sf::Vector2f> positions;
    std::vector<sf::Vector2f> texCoords;
    for(int i = 0; i < 11; ++i) {
        sf::Vector2f flarePos(sunPos + flarePosInc * (float)(i+1));
        float texCoords1 = texIndex[i] / 9.0f;
        float texCoords2 = texCoords1 + 1.0f / 9.0f;
        positions.emplace_back(flarePos.x - radiusX * scale[i], flarePos.y + radiusY * scale[i]);     texCoords.emplace_back(texCoords1, 1.0f);
        positions.emplace_back(flarePos.x - radiusX * scale[i], flarePos.y - radiusY * scale[i]);     texCoords.emplace_back(texCoords1, 0.0f);
        positions.emplace_back(flarePos.x + radiusX * scale[i], flarePos.y + radiusY * scale[i]);     texCoords.emplace_back(texCoords2, 1.0f);
        positions.emplace_back(flarePos.x + radiusX * scale[i], flarePos.y + radiusY * scale[i]);     texCoords.emplace_back(texCoords2, 1.0f);
        positions.emplace_back(flarePos.x - radiusX * scale[i], flarePos.y - radiusY * scale[i]);     texCoords.emplace_back(texCoords1, 0.0f);
        positions.emplace_back(flarePos.x + radiusX * scale[i], flarePos.y - radiusY * scale[i]);     texCoords.emplace_back(texCoords2, 0.0f);
    }

    model.vertexCount = positions.size();
    model.updateVBO(std::string("positions"), positions.size() * sizeof(sf::Vector2f), positions.data());
    model.updateVBO(std::string("texCoords"), texCoords.size() * sizeof(sf::Vector2f), texCoords.data());
}