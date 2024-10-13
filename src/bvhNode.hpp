#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "triangleFace.hpp"


struct BVHNode
{
    // TODO: integrate this code 
    BVHNode( BVHNode* parent ) :
    parent( parent ) {}
    BVHNode() = default;
    ~BVHNode()
    {
        delete left;
        delete right;
    }

    glm::vec3 highest = {};
    glm::vec3 lowest = {};

    BVHNode* parent = nullptr;
    BVHNode* left = nullptr;
    BVHNode* right = nullptr;

    std::vector<TriangleFace> triangleFaces;
};