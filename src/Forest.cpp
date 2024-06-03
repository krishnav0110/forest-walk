#include <iostream>
#include "Forest.hpp"
#include "settings.h"
#include "Math.hpp"
#include "TreeGenerator.hpp"

Forest::Forest(): random(time(NULL)) {
    lastZ = 0.0f;
    windForce = 0.0f;
    windx = 0.0f;
    
    // grass.emplace_back(new GrassBlade(sf::Vector3f(0.0f, 0.0f, -0.2f), 0.02f, Math::PI / 24, 12.0f));

    std::vector<sf::Vector3f> positions;
    std::vector<float> widths;
    branchesModel.load(positions.size(), GL_LINES);
    branchesModel.vao.Bind();
    branchesModel.loadVBO(std::string("positions"), 200000 * sizeof(sf::Vector3f), 3, sizeof(sf::Vector3f), positions.data(), GL_DYNAMIC_DRAW);
    branchesModel.loadVBO(std::string("widths"), 200000 * sizeof(float), 1, sizeof(float), widths.data(), GL_DYNAMIC_DRAW);
    branchesModel.vao.Unbind();

    std::vector<sf::Vector3f> leafPositions;
    leavesModel.load(leafPositions.size(), GL_LINES);
    leavesModel.vao.Bind();
    leavesModel.loadVBO(std::string("positions"), 100000 * sizeof(sf::Vector3f), 3, sizeof(sf::Vector3f), leafPositions.data(), GL_DYNAMIC_DRAW);
    leavesModel.vao.Unbind();

    leafTex.loadFromFile("res/tex/mapleleaf.bmp");
}

void Forest::generate(Camera &camera) {
    if(camera.pos.z > lastZ) {
        return;
    }
    for(int i = 0; i < grass.size(); ++i) {
        if(grass[i]->pos.z > camera.pos.z) {
            delete grass[i];
            grass.erase(grass.begin() + i);
            --i;
        }
    }
    for(int i = 0; i < trees.size(); ++i) {
        if(trees[i]->pos.z > camera.pos.z) {
            delete trees[i];
            trees.erase(trees.begin() + i);
            --i;
        }
    }

    lastZ -= 0.1f;
    float z = camera.pos.z - 1.2f;
    float grassSpacing = 0.0015f;
    float xMax = 0.6f;

    for(float x = -xMax; x < xMax; x += grassSpacing) {
        float len = 0.02f + 0.01f * random() / random.max();
        float angle = Math::PI / 12 * (1 - 2.0f * random() / random.max());
        float stiffness = 10 + 10.0f * random() / random.max();
        grass.emplace_back(new GrassBlade(sf::Vector3f(x, 0.0f, z), len, angle, stiffness));
    }
    TreeGenerator treeGenerator(random);
    Tree *t1 = treeGenerator.generate(sf::Vector3f(0.55f * random() / random.max(), 0.0f, z));
    trees.emplace_back(t1);
    Tree *t2 = treeGenerator.generate(sf::Vector3f(-0.55f * random() / random.max(), 0.0f, z));
    trees.emplace_back(t2);
}

void Forest::update(float dt, Camera &camera) {
    windx += (0.1f + 0.4f * random() / random.max()) * dt;
    windForce += (cosf(windx)*cosf(windx*3)*cosf(windx*5)*cosf(windx*7)+sinf(windx*25)*0.1f) * 10.0f;
    // windForce *= 10.0f;
    windForce *= 0.5f;

    std::vector<sf::Vector3f> vertices;
    std::vector<sf::Vector3f> leafVertices;
    std::vector<float> widths;
    for(GrassBlade *blade: grass) {
        if(!camera.zWithinCamera(glm::vec3(blade->pos.x, blade->pos.y, blade->pos.z))) {
            continue;
        }
        blade->applyForce(sf::Vector2f(windForce, 0.0f));
        blade->update(dt);
        blade->addVertices(vertices, widths);
    }
    for(Tree *tree: trees) {
        if(!camera.circleWithinCamera(glm::vec3(tree->pos.x, tree->pos.y, tree->pos.z), 0.01f)) {
            continue;
        }
        tree->applyForce(sf::Vector2f(windForce, 0.0f));
        tree->update(dt);
        tree->addVertices(vertices, widths);
        tree->addLeafVertices(leafVertices);
    }

    branchesModel.vertexCount = vertices.size();
    branchesModel.updateVBO(std::string("positions"), vertices.size() * sizeof(sf::Vector3f), vertices.data());
    branchesModel.updateVBO(std::string("widths"), widths.size() * sizeof(float), widths.data());

    leavesModel.vertexCount = leafVertices.size();
    leavesModel.updateVBO(std::string("positions"), leafVertices.size() * sizeof(sf::Vector3f), leafVertices.data());
}

Forest::~Forest() {
    for(GrassBlade *blade: grass) {
        delete blade;
    }
    for(Tree *tree: trees) {
        delete tree;
    }
    grass.clear();
    trees.clear();
}