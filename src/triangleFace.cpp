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
