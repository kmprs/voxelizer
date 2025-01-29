#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <glm/vec3.hpp>
#include "octreeNode.hpp"
#include "voxel.hpp"
#include "triangleFace.hpp"


namespace util
{
    [[nodiscard]] std::vector<std::string> split( const std::string &s, char delimiter );
    [[nodiscard]] float findMax( const std::vector<glm::vec3> &input );
    bool differentSign( float test, float a, float b );
    bool doIntervalsIntersect( const std::array<float, 2> &interval0,
                               const std::array<float, 2> &interval1 );

    namespace string
    {
        std::string toString( VoxelizationAlgorithm algorithm );

        template<typename T>
        std::string removeExtension( const T &filename )
        {
            typename T::size_type const p(filename.find_last_of('.'));
            return p > 0 && p != T::npos ? filename.substr(0, p) : filename;
        }
        template<typename T>
        std::string getNameFromPath( const T &path, const T &delimiters = "/" )
        {
            return removeExtension<T>(path.substr(path.find_last_of(delimiters) + 1));
        }

        VoxelizationAlgorithm toAlgorithm( const std::string &s );

        std::string generateRandomString(int length);

    }

    namespace geometry
    {
        [[nodiscard]] std::array<Triangle, 12>
        getCubeTriangles( const glm::vec3 &positions, float edgeLength );
        std::vector<glm::vec3>
        extractPositions(
                const vecTriangleFaceSharedPtr &triangleFaces );
        glm::vec3 minVec( const std::vector<glm::vec3> &vectors );
        glm::vec3 maxVec( const std::vector<glm::vec3> &vectors );
        bool doBoundingVolumesIntersect( const glm::vec3 &min1, const glm::vec3 &max1,
                                         const glm::vec3 &min2, const glm::vec3 &max2 );
        bool doTrianglesIntersect( const Triangle &t0, const Triangle &t1 );
        bool isInsideBox( const Triangle &triangle, const glm::vec3 &minAABB,
                          const glm::vec3 &maxAABB );
        float computePlaneDistance( const glm::vec3 &normal, const glm::vec3 &point,
                                    float distance );
        std::array<float, 2> computeTriangleLineInterval( const Triangle &triangle,
                                                          const glm::vec3 &intersectionDirection,
                                                          const std::array<float, 3> &distances );
        float
        projectOntoAxis( const glm::vec3 &distance, const glm::vec3 &trianglePoint );
        glm::vec3 calculateCentroid( const vecTriangleFaceSharedPtr &triangleFaces );
    }

    namespace octree
    {
        void findleavesAtMaxDepth( OctreeNode* node, int depth, int &maxDepth,
                                   std::vector<OctreeNode*> &leaves );

        std::vector<Voxel> toVoxel( OctreeNode* node, int depth );
    }

    namespace voxel
    {
        Voxel
        createVoxel( const glm::vec3 &position, unsigned int offset, float edgeLength );
    }

    namespace bvh
    {
        void createChildren( BVHNode* node, int depth, int maxDepth );
        void getLeaves( BVHNode* node, std::vector<BVHNode*> &leaves );
    }

    namespace time
    {
        float toMS( const Duration &duration );
        std::string getCurrentDateTime();
        double calculateMean( const std::vector<long long> &times );
        double calculateStandardDeviation( const std::vector<long long> &times, double
        mean);
    }
}