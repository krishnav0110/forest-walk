#ifndef _FOREST_H_
#define _FOREST_H_

#include <random>
#include "Camera.hpp"
#include "core/Model.hpp"
#include "GrassBlade.hpp"
#include "Tree.hpp"

class Forest {
private:
    std::default_random_engine random;
    std::vector<GrassBlade*> grass;
    std::vector<Tree*> trees;
    float lastZ;

public:
    float windForce;
    float windx;
    Model branchesModel;
    Model leavesModel;
    sf::Texture leafTex;

    Forest();
    ~Forest();
    void Generate(const Camera &camera);
    void Update(float dt, const Camera &camera);
};

#endif