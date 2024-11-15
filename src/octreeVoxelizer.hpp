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
    run( const vecTriangleFace &triangleFaces,
         int resolution ) override;

private:
    void buildOctree( OctreeNode* octreeNode, int depth, int maxDepth,
                      const vecTriangleFace &triangleFaces );
};
