#ifndef _TREE_H_
#define _TREE_H_

#include <SFML/Graphics.hpp>
#include "PivotRod.hpp"

class TreeGenerator;

struct Leaf {
    sf::Vector3f pos;
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
    sf::Vector3f pos;
    Tree(sf::Vector3f &pos);
    void applyForce(sf::Vector2f &force);
    void update(float dt);
    void addVertices(std::vector<sf::Vector3f> &vertices, std::vector<float> &widths);
    void addLeafVertices(std::vector<sf::Vector3f> &vertices);
    ~Tree();
};

#endif