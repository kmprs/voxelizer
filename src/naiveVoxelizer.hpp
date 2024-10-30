#pragma once


#include "voxelizer.hpp"
#include "dataHandler.hpp"
#include "util.hpp"

class NaiveVoxelizer : public Voxelizer
{
public:
    NaiveVoxelizer() = default;
    std::vector<Voxel>
    run( const std::vector<std::shared_ptr<TriangleFace>> &triangleFaces, int resolution ) override;
};