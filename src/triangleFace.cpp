#include "triangleFace.hpp"


TriangleFace::TriangleFace( const Vertex* vertices, unsigned int offset )
        :
        m_vertices{ vertices[0], vertices[1], vertices[2] }
{
    m_indices[0] = offset + 0;
    m_indices[1] = offset + 1;
    m_indices[2] = offset + 2;

    m_center = util::geometry::calculateCenter(
            { m_vertices[0].x, m_vertices[0].y, m_vertices[0].z },
            { m_vertices[1].x, m_vertices[1].y, m_vertices[1].z },
            { m_vertices[2].x, m_vertices[2].y, m_vertices[2].z }
    );
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

