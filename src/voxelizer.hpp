#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include "voxel.hpp"
#include "triangleFace.hpp"


class Voxelizer
{
public:
    std::vector<std::shared_ptr<Voxel>>
    convert( const std::vector<std::shared_ptr<TriangleFace>> &triangleFaces );

private:
    [[nodiscard]] Voxel
    createVoxel( const glm::vec3 &position, unsigned int offset, float edgeLength ) const;
};


