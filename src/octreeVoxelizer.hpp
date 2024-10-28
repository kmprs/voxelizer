#pragma once

#include <glm/vec3.hpp>
#include "octreeNode.hpp"
#include "util.hpp"
#include "constants.hpp"
#include "voxelizer.hpp"
#include "dataHandler.hpp"


class OctreeVoxelizer : public Voxelizer
{
public:
    OctreeVoxelizer() = default;

    std::vector<Voxel>
    run( const std::vector<std::shared_ptr<TriangleFace>> &triangleFaces, int resolution ) override;
    void
    buildOctree( OctreeNode* octreeNode, int depth, int maxDepth,
                 std::vector<BVHNode*> &leaves, long &counter );

private:
    static bool doTrianglesIntersect( const Triangle &t0, const Triangle &t1 );
    static bool isInsideBox( const Triangle &triangle, const glm::vec3 &minAABB, const glm::vec3 &maxAABB);
    static float
    computePlaneDistance( const glm::vec3 &normal, const glm::vec3 &point,
                          float distance );
    static std::array<float, 2>
    computeTriangleLineInterval( const Triangle &triangle,
                                 const glm::vec3 &intersectionDirection,
                                 const std::array<float, 3> &distances );
    static float
    projectOntoAxis( const glm::vec3 &distance, const glm::vec3 &trianglePoint );
};


