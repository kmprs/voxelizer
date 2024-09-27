#pragma once

#include "renderableObject.hpp"
#include "types.hpp"

class Voxel : public RenderableObject
{
public:
    Voxel( const VoxelFace &front, const VoxelFace &back, const VoxelFace &top, const VoxelFace &bottom,
           const VoxelFace &left, const VoxelFace &right )
            :
            front( front ), back( back ), top( top ), bottom( bottom ), left( left ), right( right )
    {};
    Voxel() = default;

    [[nodiscard]] std::vector<float> getVertexData() const override;
    [[nodiscard]] std::vector<unsigned int> getIndices() const override;

private:
    VoxelFace front = {};
    VoxelFace back = {};
    VoxelFace top = {};
    VoxelFace bottom = {};
    VoxelFace left = {};
    VoxelFace right = {};
};