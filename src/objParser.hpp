#pragma once

#include "parser.hpp"


class OBJParser : public Parser
{
public:
    OBJParser() = default;
    [[nodiscard]] std::vector<std::shared_ptr<TriangleFace>> parse( const std::string &path) const override;
};