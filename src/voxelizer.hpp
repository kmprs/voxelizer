#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include "voxel.hpp"
#include "triangleFace.hpp"
#include "octreeNode.hpp"


class Voxelizer
{
public:
    Voxelizer(const std::vector<std::shared_ptr<TriangleFace>> &triangleFaces);
    Voxelizer() = default;
    void
    buildOctree( OctreeNode* node, int depth, int maxDepth);

private:
    std::vector<Triangle> m_meshTriangles = {};
    static bool doTrianglesIntersect(const Triangle& t0, const Triangle& t1);
};


