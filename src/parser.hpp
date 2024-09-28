#pragma once


#include <vector>
#include "triangleFace.hpp"

class Parser
{
public:
    [[nodiscard]] virtual std::vector<std::shared_ptr<TriangleFace>> parse( const std::string &path) const = 0;

    virtual ~Parser() = default;
};