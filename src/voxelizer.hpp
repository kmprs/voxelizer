#pragma once

#include <vector>
#include "voxel.hpp"
#include "triangleFace.hpp"


class Voxelizer
{
public:
    static std::vector<std::shared_ptr<Voxel>> convert(
            std::vector<std::shared_ptr<TriangleFace>>
    );
private:

};


