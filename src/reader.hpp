#pragma once


#include <vector>
#include "triangleFace.hpp"

class Reader
{
public:
    [[nodiscard]] virtual std::vector<std::shared_ptr<TriangleFace>> read(const std::string &path) const = 0;

    ~Reader() = default;
};