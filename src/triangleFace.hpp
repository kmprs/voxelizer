#pragma once

#include "renderable.hpp"
#include "types.hpp"

class TriangleFace : public Renderable
{
public:
    TriangleFace( const Vertex vertices[3], unsigned int offset ) :
            vertices{ vertices[0], vertices[1], vertices[2] }
    {
        indices[0] = offset + 0;
        indices[1] = offset + 1;
        indices[2] = offset + 2;
    };

    [[nodiscard]] std::vector<float> getVertexData() const override;
    [[nodiscard]] std::vector<unsigned int> getIndices() const override;
    [[nodiscard]] Triangle toTriangle();

private:
    Vertex vertices[3] = {};
    unsigned int indices[3] = {};
};