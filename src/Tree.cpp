#include "Tree.hpp"
#include "util/MathUtil.hpp"

Leaf::Leaf(PivotRod *parent) {
    this->parent = parent;
    this->pos = {0.0f, 0.0f, 0.0f};
}

Tree::Tree(const glm::vec3 &pos) {
    this->pos = pos;
}

void Tree::ApplyForce(const glm::vec2 &force) {
    for(PivotRod *rod: branches) {
        rod->ApplyForce(force);
    }
    for(PivotRod *leaf: leaves) {
        leaf->ApplyForce(force);
    }
}

void Tree::Update(float dt) {
    branches[0]->pos = pos;
    for(PivotRod *rod: branches) {
        if(rod->parent != NULL) {
            rod->pos = rod->parent->endPos;
        }
        rod->Update(dt);
    }
    for(PivotRod *leaf: leaves) {
        leaf->pos = leaf->parent->endPos;
        leaf->Update(dt);
    }
}

void Tree::AddVertices(std::vector<glm::vec3> &vertices) {
    for(int i = 0; i < branches.size(); ++i) {
        PivotRod *rod = branches[i];
        vertices.emplace_back(rod->pos);
        vertices.emplace_back(rod->endPos);
    }
}

void Tree::AddVertices(std::vector<glm::vec3> &vertices, std::vector<float> &widths) {
    for(int i = 0; i < branches.size(); ++i) {
        PivotRod *rod = branches[i];
        vertices.emplace_back(rod->pos);
        widths.emplace_back(width[i]);
        vertices.emplace_back(rod->endPos);
        widths.emplace_back(width[i]);
    }
}

void Tree::AddLeafVertices(std::vector<glm::vec3> &vertices) {
    for(PivotRod *leaf: leaves) {
        vertices.emplace_back(leaf->pos);
        vertices.emplace_back(leaf->endPos);
    }
}

Tree::~Tree() {
    for(PivotRod *rod: branches) {
        delete rod;
    }
    branches.clear();
    for(PivotRod *leaf: leaves) {
        delete leaf;
    }
    leaves.clear();
}