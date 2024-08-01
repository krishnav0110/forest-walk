#ifndef _FOREST_H_
#define _FOREST_H_

#include <random>
#include "Camera.hpp"
#include "core/Model.hpp"
#include "GrassBlade.hpp"
#include "Tree.hpp"

struct ForestLayer {
    float z;
    GLintptr branchesVboOffset;
    GLsizeiptr branchesVboSize;

    GLintptr branchWidthsVboOffset;
    GLsizeiptr branchWidthsVboSize;

    GLintptr leafVboOffset;
    GLsizeiptr leafVboSize;

    std::vector<GrassBlade*> grass;
    std::vector<Tree*> trees;
};

class Forest {
private:
    const static int LAYER_COUNT;
    const static float GRASS_X_MAX;
    const static float GRASS_SPACING;
    const static float LAYER_Z_START_FROM_CAMERA;
    const static float LAYER_Z_SPACING;
    const static float LAYER_Z_UPDATE_RANGE;

    std::default_random_engine random;
    std::vector<ForestLayer> forestLayers;

    void Init();

public:
    float windForce;
    float windx;
    Model branchesModel;
    Model leavesModel;
    sf::Texture leafTex;

    Forest();
    ~Forest();
    void UpdateLayer(ForestLayer &forestLayer, const Camera &camera);
    void Update(float dt, const Camera &camera);
};

#endif