#pragma once

#include "voxelizer.hpp"
#include "octreeNode.hpp"
#include "dataHandler.hpp"
#include "util.hpp"


class OctreeVoxelizer : public Voxelizer
{
public:
    OctreeVoxelizer() = default;

    std::vector<Voxel>
    run( const vecTriangleFaceSharedPtr &triangleFaces,
         int resolution ) override;

private:
    void buildOctree( OctreeNode* octreeNode, int depth, int maxDepth,
                      const vecTriangleFaceSharedPtr &triangleFaces );
};
