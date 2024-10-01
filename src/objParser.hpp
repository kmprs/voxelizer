#pragma once

#include "parser.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <glm/vec3.hpp>


class OBJParser : public Parser
{
public:
    OBJParser() = default;
    [[nodiscard]] std::vector<std::shared_ptr<TriangleFace>> parse( const std::string &path ) override;


private:
    std::vector<glm::vec3> m_positions = {};
    std::vector<glm::vec3> m_normals = {};
    std::vector<OBJFaceIndices> m_faceIndices = {};

    static std::vector<OBJFaceIndices> toFaceIndices( const std::vector<std::string> &fInput ) ;
    [[nodiscard]] static std::vector<std::string> split( const std::string &s, char delimiter );
    [[nodiscard]] static float findMax( const std::vector<glm::vec3> &input );
};