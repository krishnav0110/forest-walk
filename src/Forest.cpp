#include <iostream>
#include "Forest.hpp"
#include "util/MathUtil.hpp"
#include "TreeGenerator.hpp"

Forest::Forest(): random((unsigned int)time(NULL)) {
    lastZ = 0.0f;
    windForce = 0.0f;
    windx = 0.0f;

    std::vector<glm::vec3> positions;
    std::vector<float> widths;
    branchesModel.Update((unsigned int)positions.size(), GL_LINES);
    branchesModel.vao.Bind();
    branchesModel.LoadVBO(std::string("positions"), 200000 * sizeof(glm::vec3), 3, sizeof(glm::vec3), positions.data(), GL_DYNAMIC_DRAW);
    branchesModel.LoadVBO(std::string("widths"), 200000 * sizeof(float), 1, sizeof(float), widths.data(), GL_DYNAMIC_DRAW);
    branchesModel.vao.Unbind();

    std::vector<glm::vec3> leafPositions;
    leavesModel.Update((unsigned int)leafPositions.size(), GL_LINES);
    leavesModel.vao.Bind();
    leavesModel.LoadVBO(std::string("positions"), 100000 * sizeof(glm::vec3), 3, sizeof(glm::vec3), leafPositions.data(), GL_DYNAMIC_DRAW);
    leavesModel.vao.Unbind();

    leafTex.loadFromFile("res/tex/mapleleaf.bmp");
}

void Forest::Generate(const Camera &camera) {
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
    float z = camera.pos.z - 2.0f;
    float grassSpacing = 0.0015f;
    float xMax = 0.6f;

    for(float x = -xMax; x < xMax; x += grassSpacing) {
        float len = 0.02f + 0.01f * random() / random.max();
        float angle = MathUtil::PI / 12 * (1 - 2.0f * random() / random.max());
        float stiffness = 10 + 10.0f * random() / random.max();
        grass.emplace_back(new GrassBlade(glm::vec3(x, 0.0f, z), len, angle, stiffness));
    }
    TreeGenerator treeGenerator(random);
    Tree *t1 = treeGenerator.Generate(glm::vec3(0.55f * random() / random.max(), 0.0f, z));
    trees.emplace_back(t1);
    Tree *t2 = treeGenerator.Generate(glm::vec3(-0.55f * random() / random.max(), 0.0f, z));
    trees.emplace_back(t2);
}

void Forest::Update(float dt, const Camera &camera) {
    windx += (0.1f + 0.4f * random() / random.max()) * dt;
    windForce += (cosf(windx)*cosf(windx*3)*cosf(windx*5)*cosf(windx*7)+sinf(windx*25)*0.1f) * 10.0f;
    // windForce *= 10.0f;
    windForce *= 0.5f;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> leafVertices;
    std::vector<float> widths;
    for(GrassBlade *blade: grass) {
        if(!camera.ZWithinCamera(glm::vec3(blade->pos.x, blade->pos.y, blade->pos.z))) {
            continue;
        }
        blade->ApplyForce(glm::vec2(windForce, 0.0f));
        blade->Update(dt);
        blade->AddVertices(vertices, widths);
    }
    for(Tree *tree: trees) {
        if(!camera.CircleWithinCamera(glm::vec3(tree->pos.x, tree->pos.y, tree->pos.z), 0.01f)) {
            continue;
        }
        tree->ApplyForce(glm::vec2(windForce, 0.0f));
        tree->Update(dt);
        tree->AddVertices(vertices, widths);
        tree->AddLeafVertices(leafVertices);
    }

    branchesModel.Update((unsigned int)vertices.size());
    branchesModel.UpdateVBO(std::string("positions"), vertices.size() * sizeof(glm::vec3), vertices.data());
    branchesModel.UpdateVBO(std::string("widths"), widths.size() * sizeof(float), widths.data());

    leavesModel.Update((unsigned int)leafVertices.size());
    leavesModel.UpdateVBO(std::string("positions"), leafVertices.size() * sizeof(glm::vec3), leafVertices.data());
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