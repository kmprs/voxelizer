#pragma once

#include "renderable.hpp"
#include "types.hpp"


class TriangleFace : public Renderable
{
public:
    TriangleFace( const Vertex vertices[3], unsigned int offset );

    [[nodiscard]] std::vector<float> getVertexData() const override;
    [[nodiscard]] std::vector<unsigned int> getIndices() const override;
    [[nodiscard]] Triangle toTriangle() const;
    [[nodiscard]] glm::vec3 getCenter() const;

private:
    Vertex m_vertices[3] = {};
    unsigned int m_indices[3] = {};
    glm::vec3 m_center = {};
};