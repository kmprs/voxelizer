#include "triangleFace.hpp"


TriangleFace::TriangleFace( const Vertex* vertices, unsigned int offset )
        :
        m_vertices{ vertices[0], vertices[1], vertices[2] }
{
    m_indices[0] = offset + 0;
    m_indices[1] = offset + 1;
    m_indices[2] = offset + 2;


    glm::vec3 pos0 = { m_vertices[0].x, m_vertices[0].y, m_vertices[0].z };
    glm::vec3 pos1 = { m_vertices[1].x, m_vertices[1].y, m_vertices[1].z };
    glm::vec3 pos2 = { m_vertices[2].x, m_vertices[2].y, m_vertices[2].z };

    m_center = { ( pos0.x + pos1.x + pos2.x ) / 3,
                 ( pos0.y + pos1.y + pos2.y ) / 3,
                 ( pos0.z + pos1.z + pos2.z ) / 3 };
};

std::vector<float> TriangleFace::getVertexData() const
{
    std::vector<float> result = {};
    for ( Vertex vertex: m_vertices )
    {
        std::vector<float> vertexData = vertex.toVector();
        result.insert( result.end(), vertexData.begin(), vertexData.end());
    }
    return result;
}

std::vector<unsigned int> TriangleFace::getIndices() const
{
    return { std::begin( m_indices ), std::end( m_indices ) };
}

Triangle TriangleFace::toTriangle() const
{
    return {{ m_vertices[0].x, m_vertices[0].y, m_vertices[0].z },
            { m_vertices[1].x, m_vertices[1].y, m_vertices[1].z },
            { m_vertices[2].x, m_vertices[2].y, m_vertices[2].z }};
}


glm::vec3 TriangleFace::getCenter() const
{
    return m_center;
}

