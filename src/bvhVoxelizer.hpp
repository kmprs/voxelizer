#pragma once


#include "voxelizer.hpp"
#include "bvhNode.hpp"
#include "util.hpp"
#include "constants.hpp"
#include "dataHandler.hpp"


class BVHVoxelizer : public Voxelizer
{
public:
    BVHVoxelizer() = default;
    std::vector<Voxel>
    run( const vecTriangleFace &triangleFaces,
         int resolution ) override;
};