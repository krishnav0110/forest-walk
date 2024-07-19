#include "Sky.hpp"

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
};

Sky::Sky(const glm::ivec2 &windowSize) {
    glm::vec3 c1(0.12f, 0.13f, 0.30f);
    glm::vec3 c2(0.12f, 0.13f, 0.30f);
    glm::vec3 c3(0.93f, 0.42f, 0.27f);
    glm::vec3 c4(0.0f, 0.0f, 0.0f);

    Vertex p1({glm::vec3(-1.0f,  1.0f, 0.0f), c1});
    Vertex p2({glm::vec3( 1.0f,  1.0f, 0.0f), c1});
    Vertex p3({glm::vec3(-1.0f,  0.4f, 0.0f), c2});
    Vertex p4({glm::vec3( 1.0f,  0.4f, 0.0f), c2});
    Vertex p5({glm::vec3(-1.0f, -0.7f, 0.0f), c3});
    Vertex p6({glm::vec3( 1.0f, -0.7f, 0.0f), c3});
    Vertex p7({glm::vec3(-1.0f, -0.9f, 0.0f), c4});
    Vertex p8({glm::vec3( 1.0f, -0.9f, 0.0f), c4});

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> colors;
    positions.emplace_back(p1.pos);     colors.emplace_back(p1.color);
    positions.emplace_back(p2.pos);     colors.emplace_back(p2.color);
    positions.emplace_back(p3.pos);     colors.emplace_back(p3.color);
    positions.emplace_back(p4.pos);     colors.emplace_back(p4.color);

    positions.emplace_back(p5.pos);     colors.emplace_back(p5.color);
    positions.emplace_back(p6.pos);     colors.emplace_back(p6.color);
    positions.emplace_back(p7.pos);     colors.emplace_back(p7.color);
    positions.emplace_back(p8.pos);     colors.emplace_back(p8.color);

    model.vao.Bind();
    model.Update((unsigned int)positions.size(), GL_TRIANGLE_STRIP);
    model.LoadVBO(std::string("positions"), positions.size() * sizeof(glm::vec3), 3, sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);
    model.LoadVBO(std::string("colors"), colors.size() * sizeof(glm::vec3), 3, sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);
    model.vao.Unbind();

    sunPos = {-0.2f, -0.5f};
    float radiusY = 0.18f;
    float radiusX = radiusY / windowSize.x * windowSize.y;
    std::vector<glm::vec3> sunVertices;
    sunVertices.emplace_back(glm::vec3(sunPos.x - radiusX, sunPos.y + radiusY, 0.0f));
    sunVertices.emplace_back(glm::vec3(sunPos.x + radiusX, sunPos.y + radiusY, 0.0f));
    sunVertices.emplace_back(glm::vec3(sunPos.x - radiusX, sunPos.y - radiusY, 0.0f));
    sunVertices.emplace_back(glm::vec3(sunPos.x + radiusX, sunPos.y - radiusY, 0.0f));

    float sunTexCoord[] = {
        0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f
    };

    sunModel.vao.Bind();
    sunModel.Update((unsigned int)sunVertices.size(), GL_TRIANGLE_STRIP);
    sunModel.LoadVBO(std::string("positions"), sunVertices.size() * sizeof(glm::vec3), 3, sizeof(glm::vec3), sunVertices.data(), GL_STATIC_DRAW);
    sunModel.LoadVBO(std::string("textures"), sizeof(sunTexCoord), 2, 2 * sizeof(float), &sunTexCoord, GL_STATIC_DRAW);
    sunModel.vao.Unbind();

    sunTex.loadFromFile("res/tex/sun.bmp");
}