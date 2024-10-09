#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include "voxel.hpp"
#include "triangleFace.hpp"
#include "octreeNode.hpp"


class Voxelizer
{
public:
    static void
    convert( const std::vector<std::shared_ptr<TriangleFace>> &triangleFaces,
             std::unique_ptr<OctreeNode> node, int depth, int maxDepth,
             std::vector<std::shared_ptr<Voxel>> &voxels );

private:
    [[nodiscard]] static Voxel
    createVoxel( const glm::vec3 &position, unsigned int offset, float edgeLength ) ;
};


