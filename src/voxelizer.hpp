#pragma once

#include <vector>
#include <memory>
#include "triangleFace.hpp"
#include "voxel.hpp"


class Voxelizer
{
public:
    virtual std::vector<Voxel>
    run( const std::vector<std::shared_ptr<TriangleFace>> &triangleFaces,
         int resolution ) = 0;
    virtual ~Voxelizer() = default;
};