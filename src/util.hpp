#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/vec3.hpp>
#include "octreeNode.hpp"


namespace util
{
    [[nodiscard]] std::vector<std::string> split( const std::string &s, char delimiter );
    [[nodiscard]] float findMax( const std::vector<glm::vec3> &input );
    void findleavesAtMaxDepth( OctreeNode* node, int depth, int &maxDepth,
                               std::vector<OctreeNode*> &leaves );
}