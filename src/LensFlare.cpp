#include "LensFlare.hpp"

LensFlare::LensFlare(const glm::ivec2 &windowSize) {
    this->windowSize = glm::vec2(windowSize);
    std::vector<glm::vec2> positions;
    std::vector<glm::vec2> texCoords;

    model.vao.Bind();
    model.Update((unsigned int)positions.size(), GL_TRIANGLES);
    model.LoadVBO(std::string("positions"), 66 * sizeof(glm::vec2), 2, sizeof(glm::vec2), positions.data(), GL_DYNAMIC_DRAW);
    model.LoadVBO(std::string("texCoords"), 66 * sizeof(glm::vec2), 2, sizeof(glm::vec2), texCoords.data(), GL_DYNAMIC_DRAW);
    model.vao.Unbind();

    flareTex.loadFromFile("res/tex/flare.png");
}

void LensFlare::Update(const glm::vec2 &sunPos) {
    glm::vec2 sunToCenter(-sunPos.x, -sunPos.y);
    float length = sqrtf(sunToCenter.x * sunToCenter.x + sunToCenter.y * sunToCenter.y);
    this->alpha = 1.0f - length / 0.62f;

    glm::vec2 flarePosInc(sunToCenter / 6.0f);
    int texIndex[11] = {5, 3, 1, 6, 2, 4, 6, 2, 4, 3, 7};
    float scale[11] = {0.125f, 0.23f, 0.05f, 0.025f, 0.0015f, 0.0175f, 0.1f, 0.0175f, 0.075f, 0.4f, 0.6f};
    float radiusY = 0.6f;
    float radiusX = radiusY / windowSize.x * windowSize.y;

    std::vector<glm::vec2> positions;
    std::vector<glm::vec2> texCoords;
    for(int i = 0; i < 11; ++i) {
        glm::vec2 flarePos(sunPos + flarePosInc * (float)(i+1));
        float texCoords1 = texIndex[i] / 9.0f;
        float texCoords2 = texCoords1 + 1.0f / 9.0f;
        positions.emplace_back(flarePos.x - radiusX * scale[i], flarePos.y + radiusY * scale[i]);     texCoords.emplace_back(texCoords1, 1.0f);
        positions.emplace_back(flarePos.x - radiusX * scale[i], flarePos.y - radiusY * scale[i]);     texCoords.emplace_back(texCoords1, 0.0f);
        positions.emplace_back(flarePos.x + radiusX * scale[i], flarePos.y + radiusY * scale[i]);     texCoords.emplace_back(texCoords2, 1.0f);
        positions.emplace_back(flarePos.x + radiusX * scale[i], flarePos.y + radiusY * scale[i]);     texCoords.emplace_back(texCoords2, 1.0f);
        positions.emplace_back(flarePos.x - radiusX * scale[i], flarePos.y - radiusY * scale[i]);     texCoords.emplace_back(texCoords1, 0.0f);
        positions.emplace_back(flarePos.x + radiusX * scale[i], flarePos.y - radiusY * scale[i]);     texCoords.emplace_back(texCoords2, 0.0f);
    }

    model.Update((unsigned int)positions.size());
    model.UpdateVBO(std::string("positions"), positions.size() * sizeof(glm::vec2), positions.data());
    model.UpdateVBO(std::string("texCoords"), texCoords.size() * sizeof(glm::vec2), texCoords.data());
}