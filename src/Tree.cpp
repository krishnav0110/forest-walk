#include "Tree.hpp"
#include "Math.hpp"

Leaf::Leaf(PivotRod *parent) {
    this->parent = parent;
    this->pos = {0.0f, 0.0f, 0.0f};
}

Tree::Tree(sf::Vector3f &pos) {
    this->pos = pos;
}

void Tree::applyForce(sf::Vector2f &force) {
    for(PivotRod *rod: branches) {
        rod->applyForce(force);
    }
    for(PivotRod *leaf: leaves) {
        leaf->applyForce(force);
    }
}

void Tree::update(float dt) {
    branches[0]->pos = pos;
    for(PivotRod *rod: branches) {
        if(rod->parent != NULL) {
            rod->pos = rod->parent->endPos;
        }
        rod->update(dt);
    }
    for(PivotRod *leaf: leaves) {
        leaf->pos = leaf->parent->endPos;
        leaf->update(dt);
    }
}

void Tree::addVertices(std::vector<sf::Vector3f> &vertices, std::vector<float> &widths) {
    for(int i = 0; i < branches.size(); ++i) {
        PivotRod *rod = branches[i];
        vertices.emplace_back(rod->pos);
        widths.emplace_back(width[i]);
        vertices.emplace_back(rod->endPos);
        widths.emplace_back(width[i]);
    }
}

void Tree::addLeafVertices(std::vector<sf::Vector3f> &vertices) {
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