#ifndef _TREE_H_
#define _TREE_H_

#include <SFML/Graphics.hpp>
#include "PivotRod.hpp"

class TreeGenerator;

struct Leaf {
    glm::vec3 pos;
    PivotRod *parent;

    Leaf(PivotRod *parent);
};

class Tree {
private:
    std::vector<float> width;
    std::vector<PivotRod*> branches;
    std::vector<PivotRod*> leaves;

    friend class TreeGenerator;

public:
    glm::vec3 pos;
    Tree(const glm::vec3 &pos);
    void ApplyForce(const glm::vec2 &force);
    void Update(float dt);
    void AddVertices(std::vector<glm::vec3> &vertices);
    void AddVertices(std::vector<glm::vec3> &vertices, std::vector<float> &widths);
    void AddLeafVertices(std::vector<glm::vec3> &vertices);
    ~Tree();
};

#endif