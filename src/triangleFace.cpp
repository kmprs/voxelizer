#include "triangleFace.hpp"

std::vector<float> TriangleFace::getVertexData() const
{
    std::vector<float> result = {};
    for ( Vertex vertex: vertices )
    {
        std::vector<float> vertexData = vertex.toVector();
        result.insert( result.end(), vertexData.begin(), vertexData.end());
    }
    return result;
}

std::vector<unsigned int> TriangleFace::getIndices() const
{
    return { std::begin( indices ), std::end( indices ) };
}

Triangle TriangleFace::toTriangle()
{
    return {{ vertices[0].x, vertices[0].y, vertices[0].z },
            { vertices[1].x, vertices[1].y, vertices[1].z },
            { vertices[2].x, vertices[2].y, vertices[2].z }} ;
}
