#pragma once

#include <iostream>

class RenderableObject
{
public:
    [[nodiscard]] virtual std::vector<float> getVertexData() const = 0;
    [[nodiscard]] virtual std::vector<unsigned int> getIndices() const = 0;

    virtual ~RenderableObject() = default;
};