#pragma once

#include <iostream>

class Renderable
{
public:
    [[nodiscard]] virtual std::vector<float> getVertexData() const = 0;
    [[nodiscard]] virtual std::vector<unsigned int> getIndices() const = 0;

    virtual ~Renderable() = default;
};