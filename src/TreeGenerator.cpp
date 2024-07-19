#include <queue>

#include "TreeGenerator.hpp"
#include "util/MathUtil.hpp"

TreeGenerator::TreeGenerator(std::default_random_engine &random): random(random) {

}

Tree* TreeGenerator::Generate(const glm::vec3 &pos) {
    float drag = 2.0f;
    int iterations = 0;
    int branchIterations = 9;
    float width = 0.0f;
    float leafThreshold = pow(2, branchIterations - 1);
    for(int i = 0; i < branchIterations; ++i) {
        iterations = iterations + pow(2, i);
        width += 0.001f;
    }

    Tree *tree = new Tree(pos);

    float baseBranchLength = 0.075f;

    float branchLength = baseBranchLength + baseBranchLength * random() / random.max();
    float angle = MathUtil::HALF_PI + MathUtil::PI / 12 * (1 - 2.0f * random() / random.max());
    float stiffness = 200.0f + 200.0f * random() / random.max();

    std::queue<PivotRod*> branchQueue;
    std::queue<float> branchWidthQueue;
    branchQueue.push(tree->branches.emplace_back(new PivotRod(NULL, branchLength, angle, stiffness, drag)));
    branchWidthQueue.push(tree->width.emplace_back(width));

    while(!branchQueue.empty()) {
        PivotRod *branch = branchQueue.front();
        branchQueue.pop();
        width = branchWidthQueue.front();
        branchWidthQueue.pop();

        if(iterations > 1) {
            stiffness = branch->stiffness * 0.8f + 50.0f * random() / random.max();

            float branchWidth1 = width * 0.9f;
            float branchWidth2 = width * 0.7f;

            float branchAngle1 = MathUtil::PI / 18 * (1.0f - 2.0f * random() / random.max());
            float branchAngle2 = MathUtil::PI / 3 * (1.0f - 2.0f * random() / random.max());

            branchLength = branch->length * (0.8f + 0.1f * random() / random.max());

            PivotRod *branch1 = tree->branches.emplace_back(new PivotRod(branch, branchLength, branchAngle1, stiffness, drag));
            float width1 = tree->width.emplace_back(branchWidth1);

            PivotRod *branch2 = tree->branches.emplace_back(new PivotRod(branch, branchLength, branchAngle2, stiffness, drag));
            float width2 = tree->width.emplace_back(branchWidth2);

            branchQueue.push(branch1);
            branchQueue.push(branch2);
            branchWidthQueue.push(width1);
            branchWidthQueue.push(width2);
            --iterations;
        }
        if(iterations < leafThreshold) {
            tree->leaves.emplace_back(new PivotRod(branch, 0.03f, MathUtil::PI_2 * random() / random.max(), 5.0f, 0.1f));
        }
    }
    return tree;
}