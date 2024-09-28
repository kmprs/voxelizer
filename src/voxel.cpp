#include "voxel.hpp"

std::vector<float> Voxel::getVertexData() const
{
    std::vector<float> result = {};
    std::array<VoxelFace, 6> allFaces = { m_front, m_back, m_top, m_bottom, m_left, m_right };
    for ( VoxelFace face: allFaces )
    {
        std::vector<float> faceData = face.verticesToVector();
        result.insert( result.end(), faceData.begin(), faceData.end());
    }
    return result;
}

std::vector<unsigned int> Voxel::getIndices() const
{
    std::vector<unsigned int> result = {};
    std::array<VoxelFace, 6> allFaces = { m_front, m_back, m_top, m_bottom, m_left, m_right };
    for ( VoxelFace face: allFaces )
    {
        std::vector<unsigned int> faceIndices = face.indicesToVector();
        result.insert( result.end(), faceIndices.begin(), faceIndices.end());
    }
    return result;
}