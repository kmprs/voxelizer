#pragma once

#include <iostream>
#include "parser.hpp"
#include "util.hpp"


class OBJParser : public Parser
{
public:
    OBJParser() = default;
    [[nodiscard]] vecTriangleFace parse( const std::string &path ) override;


private:
    std::vector<glm::vec3> m_positions = {};
    std::vector<glm::vec3> m_normals = {};
    std::vector<OBJFaceIndices> m_faceIndices = {};

    static std::vector<OBJFaceIndices> toFaceIndices( const std::vector<std::string> &fInput ) ;
};