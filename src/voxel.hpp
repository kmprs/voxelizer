#pragma once

#include "renderable.hpp"
#include "types.hpp"


class Voxel : public Renderable
{
public:
    Voxel( const VoxelFace &front, const VoxelFace &back, const VoxelFace &top,
           const VoxelFace &bottom,
           const VoxelFace &left, const VoxelFace &right )
            :
            m_front( front ), m_back( back ), m_top( top ), m_bottom( bottom ),
            m_left( left ), m_right( right )
    {};

    [[nodiscard]] std::vector<float> getVertexData() const override;
    [[nodiscard]] std::vector<unsigned int> getIndices() const override;
    [[nodiscard]] glm::vec3 getPos() const;

    bool operator<( const Voxel &other ) const;
    bool operator==( const Voxel &other ) const;
    bool operator!=( const Voxel &other ) const;

private:
    VoxelFace m_front = {};
    VoxelFace m_back = {};
    VoxelFace m_top = {};
    VoxelFace m_bottom = {};
    VoxelFace m_left = {};
    VoxelFace m_right = {};
};