#pragma once


#include <vector>
#include "triangleFace.hpp"

class Parser
{
public:
    [[nodiscard]] virtual vecTriangleFace parse( const std::string &path) = 0;

    virtual ~Parser() = default;
};