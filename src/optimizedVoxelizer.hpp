#pragma once

#include <glm/vec3.hpp>
#include "octreeNode.hpp"
#include "util.hpp"
#include "constants.hpp"
#include "voxelizer.hpp"
#include "dataHandler.hpp"


class OptimizedVoxelizer : public Voxelizer
{
public:
    OptimizedVoxelizer() = default;

    std::vector<Voxel>
    run( const vecTriangleFaceSharedPtr &triangleFaces,
         int resolution ) override;
private:
    void buildOctree( OctreeNode* octreeNode, int depth, int maxDepth,
                      std::vector<BVHNode*> &leaves );
};


