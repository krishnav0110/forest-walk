#ifndef _TREE_GENERATOR_H_
#define _TREE_GENERATOR_H_

#include <random>
#include "Tree.hpp"

class TreeGenerator {
private:
    std::default_random_engine random;

public:
    TreeGenerator(std::default_random_engine &random);
    Tree* generate(sf::Vector3f &pos);
};

#endif