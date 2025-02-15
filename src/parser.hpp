#pragma once


#include <vector>
#include "triangleFace.hpp"


class Parser
{
public:
    [[nodiscard]] virtual vecTriangleFaceSharedPtr parse( const std::string &path ) = 0;

    virtual ~Parser() = default;
};