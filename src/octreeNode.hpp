#pragma once

#include <glm/vec3.hpp>
#include <array>


struct OctreeNode
{
    OctreeNode( OctreeNode* parent, float edgeLength, const glm::vec3 &position );

    OctreeNode* parent = nullptr;
    std::array<OctreeNode*, 8> children =
            {
                    nullptr, nullptr,
                    nullptr, nullptr,
                    nullptr, nullptr,
                    nullptr, nullptr
            };

    glm::vec3 position = {};
    float edgeLength = -1;
    bool isAir = false;
    bool isLeaf = true;

    void createChildren();
};