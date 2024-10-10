#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/vec3.hpp>
#include "octreeNode.hpp"
#include "triangleFace.hpp"
#include "voxel.hpp"


namespace util
{
    [[nodiscard]] std::vector<std::string> split( const std::string &s, char delimiter );
    [[nodiscard]] float findMax( const std::vector<glm::vec3> &input );
    bool differentSign (float test, float a, float b);
    bool doIntervalsIntersect(const float* interval0, const float* interval1);
    void findleavesAtMaxDepth( OctreeNode* node, int depth, int &maxDepth,
                               std::vector<OctreeNode*> &leaves );
    [[nodiscard]] std::array<Triangle, 12>
    getCubeTriangles( const glm::vec3 &positions, float edgeLength );
}