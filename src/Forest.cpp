#include <iostream>
#include "Forest.hpp"
#include "util/MathUtil.hpp"
#include "TreeGenerator.hpp"



const int Forest::LAYER_COUNT = 20;
const float Forest::GRASS_X_MAX = 0.6f;
const float Forest::GRASS_SPACING = 0.0015f;
const float Forest::LAYER_Z_START_FROM_CAMERA = LAYER_COUNT * LAYER_Z_SPACING;
const float Forest::LAYER_Z_SPACING = 0.12f;
const float Forest::LAYER_Z_UPDATE_RANGE = 1.0f;





Forest::Forest(): random((unsigned int)time(NULL)) {
    windForce = 0.0f;
    windx = 0.0f;

    std::vector<glm::vec3> positions;
    std::vector<float> branchWidths;
    branchesModel.Update((unsigned int)positions.size(), GL_LINES);
    branchesModel.vao.Bind();
    branchesModel.LoadVBO("positions", 500000 * sizeof(glm::vec3), 3, sizeof(glm::vec3), positions.data(), GL_DYNAMIC_DRAW);
    branchesModel.LoadVBO("branchWidths", 500000 * sizeof(float), 1, sizeof(float), branchWidths.data(), GL_DYNAMIC_DRAW);
    branchesModel.vao.Unbind();

    std::vector<glm::vec3> leafPositions;
    leavesModel.Update((unsigned int)leafPositions.size(), GL_LINES);
    leavesModel.vao.Bind();
    leavesModel.LoadVBO("positions", 300000 * sizeof(glm::vec3), 3, sizeof(glm::vec3), leafPositions.data(), GL_DYNAMIC_DRAW);
    leavesModel.vao.Unbind();

    leafTex.loadFromFile("res/tex/mapleleaf.bmp");

    Init();
}

void Forest::Init() {
    unsigned int branchesVerticesSize = 0;
    GLintptr previousBranchesVboOffset = 0;
    GLsizeiptr previousBranchesVboSize = 0;
    GLintptr previousBranchWidthsVboOffset = 0;
    GLsizeiptr previousBranchWidthsVboSize = 0;

    unsigned int leafVerticesSize = 0;
    GLintptr previousLeafVboOffset = 0;
    GLsizeiptr previousLeafVboSize = 0;

    for(int i = 0; i < LAYER_COUNT; ++i) {
        ForestLayer forestLayer;
        forestLayer.z = -i * LAYER_Z_SPACING;

        for(float x = -GRASS_X_MAX; x < GRASS_X_MAX; x += GRASS_SPACING) {
            float len = 0.02f + 0.01f * random() / random.max();
            float angle = MathUtil::PI / 12 * (1 - 2.0f * random() / random.max());
            float stiffness = 10 + 10.0f * random() / random.max();
            forestLayer.grass.emplace_back(new GrassBlade(glm::vec3(x, 0.0f, forestLayer.z), len, angle, stiffness));
        }

        std::vector<glm::vec3> branchVertices;
        std::vector<float> branchWidths;
        std::vector<glm::vec3> leafVertices;

        for(GrassBlade *blade: forestLayer.grass) {
            blade->Update(0.0f);
            blade->AddVertices(branchVertices, branchWidths);
        }

        TreeGenerator treeGenerator(random);
        Tree *t1 = treeGenerator.Generate(glm::vec3(0.55f * random() / random.max(), 0.0f, forestLayer.z));
        forestLayer.trees.emplace_back(t1);
        Tree *t2 = treeGenerator.Generate(glm::vec3(-0.55f * random() / random.max(), 0.0f, forestLayer.z));
        forestLayer.trees.emplace_back(t2);

        for(Tree *tree: forestLayer.trees) {
            tree->Update(0.0f);
            tree->AddVertices(branchVertices, branchWidths);
            tree->AddLeafVertices(leafVertices);
        }

        forestLayer.branchesVboOffset = previousBranchesVboOffset + previousBranchesVboSize;
        forestLayer.branchesVboSize = branchVertices.size() * sizeof(glm::vec3);
        previousBranchesVboOffset = forestLayer.branchesVboOffset;
        previousBranchesVboSize = forestLayer.branchesVboSize;

        forestLayer.branchWidthsVboOffset = previousBranchWidthsVboOffset + previousBranchWidthsVboSize;
        forestLayer.branchWidthsVboSize = branchWidths.size() * sizeof(float);
        previousBranchWidthsVboOffset = forestLayer.branchWidthsVboOffset;
        previousBranchWidthsVboSize = forestLayer.branchWidthsVboSize;

        forestLayer.leafVboOffset = previousLeafVboOffset + previousLeafVboSize;
        forestLayer.leafVboSize = leafVertices.size() * sizeof(glm::vec3);
        previousLeafVboOffset = forestLayer.leafVboOffset;
        previousLeafVboSize = forestLayer.leafVboSize;

        branchesVerticesSize += (unsigned int)branchVertices.size();
        branchesModel.UpdateVBO("positions", forestLayer.branchesVboOffset, forestLayer.branchesVboSize, branchVertices.data());
        branchesModel.UpdateVBO("branchWidths", forestLayer.branchWidthsVboOffset, forestLayer.branchWidthsVboSize, branchWidths.data());

        leafVerticesSize += (unsigned int)leafVertices.size();
        leavesModel.UpdateVBO("positions", forestLayer.leafVboOffset, forestLayer.leafVboSize, leafVertices.data());

        forestLayers.emplace_back(forestLayer);
    }
    branchesModel.Update(branchesVerticesSize);
    leavesModel.Update(leafVerticesSize);
}





void Forest::UpdateLayer(ForestLayer &forestLayer, const Camera &camera) {
    forestLayer.z -= LAYER_Z_START_FROM_CAMERA;
    std::vector<glm::vec3> branchVertices;
    std::vector<glm::vec3> leafVertices;

    for(GrassBlade *blade: forestLayer.grass) {
        blade->pos.z = forestLayer.z;
        blade->Update(0.0f);
        blade->AddVertices(branchVertices);
    }

    Tree *t1 = forestLayer.trees[0];
    Tree *t2 = forestLayer.trees[1];
    t1->pos = glm::vec3(0.55f * random() / random.max(), 0.0f, forestLayer.z);
    t2->pos = glm::vec3(-0.55f * random() / random.max(), 0.0f, forestLayer.z);

    for(Tree *tree: forestLayer.trees) {
        tree->Update(0.0f);
        tree->AddVertices(branchVertices);
        tree->AddLeafVertices(leafVertices);
    }
    
    branchesModel.UpdateVBO("positions", forestLayer.branchesVboOffset, forestLayer.branchesVboSize, branchVertices.data());
    leavesModel.UpdateVBO("positions", forestLayer.leafVboOffset, forestLayer.leafVboSize, leafVertices.data());
}





void Forest::Update(float dt, const Camera &camera) {
    windx += (0.1f + 0.4f * random() / random.max()) * dt;
    windForce += (cosf(windx)*cosf(windx*3)*cosf(windx*5)*cosf(windx*7)+sinf(windx*25)*0.1f) * 10.0f;
    windForce *= 0.5f;

    std::vector<glm::vec3> branchVertices;
    std::vector<glm::vec3> leafVertices;

    for(ForestLayer &forestLayer: forestLayers) {
        if(camera.pos.z - forestLayer.z > LAYER_Z_UPDATE_RANGE) {
            continue;
        }
        if(forestLayer.z > camera.pos.z) {
            UpdateLayer(forestLayer, camera);
        }
        branchVertices.clear();
        leafVertices.clear();

        for(GrassBlade *blade: forestLayer.grass) {
            blade->ApplyForce(glm::vec2(windForce, 0.0f));
            blade->Update(dt);
            blade->AddVertices(branchVertices);
        }
        for(Tree *tree: forestLayer.trees) {
            tree->ApplyForce(glm::vec2(windForce, 0.0f));
            tree->Update(dt);
            tree->AddVertices(branchVertices);
            tree->AddLeafVertices(leafVertices);
        }

        branchesModel.UpdateVBO("positions", forestLayer.branchesVboOffset, forestLayer.branchesVboSize, branchVertices.data());
        leavesModel.UpdateVBO("positions", forestLayer.leafVboOffset, forestLayer.leafVboSize, leafVertices.data());
    }
}





Forest::~Forest() {
    for(ForestLayer &forestLayer: forestLayers) {
        for(GrassBlade *blade: forestLayer.grass) {
            delete blade;
        }
        for(Tree *tree: forestLayer.trees) {
            delete tree;
        }
        forestLayer.grass.clear();
        forestLayer.trees.clear();
    }
}