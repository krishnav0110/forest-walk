#include "Sky.hpp"
#include "settings.h"

struct Vertex {
    sf::Vector3f pos;
    sf::Vector3f color;
};

Sky::Sky() {
    sf::Vector3f c1(0.98f, 0.75f, 0.32f);
    sf::Vector3f c2(0.93f, 0.42f, 0.27f);
    sf::Vector3f c3(0.86f, 0.45f, 0.24f);
    // sf::Vector3f c1(0.12f, 0.13f, 0.30f);
    // sf::Vector3f c2(0.93f, 0.42f, 0.27f);
    // sf::Vector3f c3(1.0f, 0.81f, 0.38f);
    sf::Vector3f c4(0.0f, 0.0f, 0.0f);

    Vertex p1({sf::Vector3f(-1.0f,  1.0f, 0.0f), c1});
    Vertex p2({sf::Vector3f( 1.0f,  1.0f, 0.0f), c1});
    Vertex p3({sf::Vector3f(-1.0f,  0.55f, 0.0f), c2});
    Vertex p4({sf::Vector3f( 1.0f,  0.55f, 0.0f), c2});
    Vertex p5({sf::Vector3f(-1.0f, -0.7f, 0.0f), c3});
    Vertex p6({sf::Vector3f( 1.0f, -0.7f, 0.0f), c3});
    Vertex p7({sf::Vector3f(-1.0f, -0.9f, 0.0f), c4});
    Vertex p8({sf::Vector3f( 1.0f, -0.9f, 0.0f), c4});

    std::vector<sf::Vector3f> positions;
    std::vector<sf::Vector3f> colors;
    positions.emplace_back(p1.pos);     colors.emplace_back(p1.color);
    positions.emplace_back(p2.pos);     colors.emplace_back(p2.color);
    positions.emplace_back(p3.pos);     colors.emplace_back(p3.color);
    positions.emplace_back(p4.pos);     colors.emplace_back(p4.color);

    positions.emplace_back(p5.pos);     colors.emplace_back(p5.color);
    positions.emplace_back(p6.pos);     colors.emplace_back(p6.color);
    positions.emplace_back(p7.pos);     colors.emplace_back(p7.color);
    positions.emplace_back(p8.pos);     colors.emplace_back(p8.color);

    model.vao.Bind();
    model.load(positions.size(), GL_TRIANGLE_STRIP);
    model.loadVBO(std::string("positions"), positions.size() * sizeof(sf::Vector3f), 3, sizeof(sf::Vector3f), positions.data(), GL_STATIC_DRAW);
    model.loadVBO(std::string("colors"), colors.size() * sizeof(sf::Vector3f), 3, sizeof(sf::Vector3f), colors.data(), GL_STATIC_DRAW);
    model.vao.Unbind();

    sunPos = {-0.2f, -0.5f};
    float radiusY = 0.16f;
    float radiusX = radiusY / WINDOW_WIDTH * WINDOW_HEIGHT;
    std::vector<sf::Vector3f> sunVertices;
    sunVertices.emplace_back(sf::Vector3f(sunPos.x - radiusX, sunPos.y + radiusY, 0.0f));
    sunVertices.emplace_back(sf::Vector3f(sunPos.x + radiusX, sunPos.y + radiusY, 0.0f));
    sunVertices.emplace_back(sf::Vector3f(sunPos.x - radiusX, sunPos.y - radiusY, 0.0f));
    sunVertices.emplace_back(sf::Vector3f(sunPos.x + radiusX, sunPos.y - radiusY, 0.0f));

    float sunTexCoord[] = {
        0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f
    };

    sunModel.vao.Bind();
    sunModel.load(sunVertices.size(), GL_TRIANGLE_STRIP);
    sunModel.loadVBO(std::string("positions"), sunVertices.size() * sizeof(sf::Vector3f), 3, sizeof(sf::Vector3f), sunVertices.data(), GL_STATIC_DRAW);
    sunModel.loadVBO(std::string("textures"), sizeof(sunTexCoord), 2, 2 * sizeof(float), &sunTexCoord, GL_STATIC_DRAW);
    sunModel.vao.Unbind();

    sunTex.loadFromFile("res/tex/sun.bmp");
}