#pragma once

#include <glm/vec3.hpp>
#include "octreeNode.hpp"
#include "util.hpp"
#include "constants.hpp"
#include "voxelizer.hpp"
#include "dataHandler.hpp"


class OctreeBVHVoxelizer : public Voxelizer
{
public:
    OctreeBVHVoxelizer() = default;

    std::vector<Voxel>
    run( const std::vector<std::shared_ptr<TriangleFace>> &triangleFaces,
         int resolution ) override;
private:
    void buildOctree( OctreeNode* octreeNode, int depth, int maxDepth,
                      std::vector<BVHNode*> &leaves, long &counter );
};


