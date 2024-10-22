#include "voxel.hpp"

std::vector<float> Voxel::getVertexData() const
{
    std::vector<float> result = {};
    std::array<VoxelFace, 6> allFaces = { m_front, m_back, m_top, m_bottom, m_left,
                                          m_right };
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
    std::array<VoxelFace, 6> allFaces = { m_front, m_back, m_top, m_bottom, m_left,
                                          m_right };
    for ( VoxelFace face: allFaces )
    {
        std::vector<unsigned int> faceIndices = face.indicesToVector();
        result.insert( result.end(), faceIndices.begin(), faceIndices.end());
    }
    return result;
}

glm::vec3 Voxel::getPos() const
{
    Vertex v = m_front.vertices[0];
    return {v.x, v.y, v.z};
}


bool Voxel::operator<(const Voxel &other) const
{
    std::vector<float> vertexData = getVertexData();
    std::vector<float> vertexDataOther = other.getVertexData();

    glm::vec3 centroid(0.0f);
    glm::vec3 centroidOther(0.0f);

    int numVertices = vertexData.size() / 6;
    for (int i = 0; i < numVertices; ++i)
    {
        centroid.x += vertexData[i * 6 + 0];
        centroid.y += vertexData[i * 6 + 1];
        centroid.z += vertexData[i * 6 + 2];
    }
    centroid /= numVertices;
    for (int i = 0; i < numVertices; ++i)
    {
        centroidOther.x += vertexDataOther[i * 6 + 0];
        centroidOther.y += vertexDataOther[i * 6 + 1];
        centroidOther.z += vertexDataOther[i * 6 + 2];
    }
    centroidOther /= numVertices;
    return glm::length(centroid) < glm::length(centroidOther);
}

bool Voxel::operator==( const Voxel &other ) const
{
    std::vector<float> vertexData = other.getVertexData();
    glm::vec3 position = { vertexData[0],
                           vertexData[1],
                           vertexData[2] };

    std::vector<float> vertexDataOther = other.getVertexData();
    glm::vec3 positionOther = { vertexDataOther[0],
                                vertexDataOther[1],
                                vertexDataOther[2] };

    return position == positionOther;
}

bool Voxel::operator!=( const Voxel &other ) const
{
    return !( *this == other );
}