#include "util.hpp"

namespace util
{
    std::vector<std::string> split( const std::string &s, char delimiter )
    {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream( s );
        while ( std::getline( tokenStream, token, delimiter ))
        {
            tokens.push_back( token );
        }
        return tokens;
    }


    float findMax( const std::vector<glm::vec3> &input )
    {
        float maximum = 0.f;
        for ( const glm::vec3 &vec: input )
        {
            maximum = std::max( { maximum, vec.x, vec.y, vec.z } );
        }
        return maximum;
    }


    bool differentSign( float test, float a, float b )
    {
        if (( test < 0 && a > 0 && b > 0 ) || ( test > 0 && a < 0 && b < 0 )) return true;
        return false;
    }


    bool doIntervalsIntersect( const std::array<float, 2> &interval0,
                               const std::array<float, 2> &interval1 )
    {
        float min0 = std::min( interval0[0], interval0[1] );
        float max0 = std::max( interval0[0], interval0[1] );

        float min1 = std::min( interval1[0], interval1[1] );
        float max1 = std::max( interval1[0], interval1[1] );

        return !( max0 < min1 || max1 < min0 );
    }

    std::string toString ( VoxelizationAlgorithm algorithm )
    {
        switch ( algorithm )
        {
            case OPTIMIZED:
                return "Optimized";
            case OCTREE:
                return "Octree";
            case BVH:
                return "BVH";
            case NAIVE:
                return "Naive";
            default:
                return "Optimized";
        }
    }


    namespace geometry
    {
        std::array<Triangle, 12>
        getCubeTriangles( const glm::vec3 &position, float edgeLength )
        {
            float halfLength = edgeLength / 2.0f;

            // Define the 8 m_vertices of the cube relative to the center
            glm::vec3 v0 = position + glm::vec3( -halfLength, -halfLength, -halfLength );
            glm::vec3 v1 = position + glm::vec3( halfLength, -halfLength, -halfLength );
            glm::vec3 v2 = position + glm::vec3( halfLength, -halfLength, halfLength );
            glm::vec3 v3 = position + glm::vec3( -halfLength, -halfLength, halfLength );
            glm::vec3 v4 = position + glm::vec3( -halfLength, halfLength, -halfLength );
            glm::vec3 v5 = position + glm::vec3( halfLength, halfLength, -halfLength );
            glm::vec3 v6 = position + glm::vec3( halfLength, halfLength, halfLength );
            glm::vec3 v7 = position + glm::vec3( -halfLength, halfLength, halfLength );

            // Create 2 triangles for each face of the cube
            std::array<Triangle, 12> triangles = {
                    // Front face
                    Triangle( v0, v1, v4 ), Triangle( v1, v5, v4 ),

                    // Back face
                    Triangle( v3, v2, v7 ), Triangle( v2, v6, v7 ),

                    // Left face
                    Triangle( v0, v3, v4 ), Triangle( v3, v7, v4 ),

                    // Right face
                    Triangle( v1, v2, v5 ), Triangle( v2, v6, v5 ),

                    // Top face
                    Triangle( v4, v5, v7 ), Triangle( v5, v6, v7 ),

                    // Bottom face
                    Triangle( v0, v1, v3 ), Triangle( v1, v2, v3 )
            };

            return triangles;
        }

        std::vector<glm::vec3>
        extractPositions(
                const std::vector<std::shared_ptr<TriangleFace>> &triangleFaces )
        {
            std::vector<glm::vec3> positions;
            for ( const std::shared_ptr<TriangleFace> &face: triangleFaces )
            {
                Triangle t = face->toTriangle();
                positions.push_back( t.position0 );
                positions.push_back( t.position1 );
                positions.push_back( t.position2 );
            }
            return positions;
        }

        glm::vec3 minVec( const std::vector<glm::vec3> &vectors )
        {
            // handle empty vector case
            if ( vectors.empty())
            {
                return { -1.0f, -1.0f, -1.0f };
            }

            glm::vec3 minVec( std::numeric_limits<float>::max());
            for ( const glm::vec3 &vec: vectors )
            {
                if ( vec.x < minVec.x ) minVec.x = vec.x;
                if ( vec.y < minVec.y ) minVec.y = vec.y;
                if ( vec.z < minVec.z ) minVec.z = vec.z;
            }

            return minVec;
        }

        glm::vec3 maxVec( const std::vector<glm::vec3> &vectors )
        {
            if ( vectors.empty())
            {
                // Handle empty vector case
                return { 1.0f, 1.0f, 1.0f };
            }

            glm::vec3 maxVec( std::numeric_limits<float>::lowest());
            for ( const glm::vec3 &vec: vectors )
            {
                if ( vec.x > maxVec.x ) maxVec.x = vec.x;
                if ( vec.y > maxVec.y ) maxVec.y = vec.y;
                if ( vec.z > maxVec.z ) maxVec.z = vec.z;
            }

            return maxVec;
        }

        bool doBoundingVolumesIntersect( const glm::vec3 &min1, const glm::vec3 &max1,
                                         const glm::vec3 &min2, const glm::vec3 &max2 )
        {
            // Check for general overlap in all dimensions
            return ( min1.x <= max2.x && max1.x >= min2.x ) &&
                   ( min1.y <= max2.y && max1.y >= min2.y ) &&
                   ( min1.z <= max2.z && max1.z >= min2.z );
        }

        bool doTrianglesIntersect( const Triangle &t0, const Triangle &t1 )
        {
            // this method is based on the algorithm presented by Thomas Moeller
            // test if triangles are on the same side of the plane build by the other triangle

            glm::vec3 normalT1 = glm::cross( t1.position1 - t1.position0,
                                             t1.position2 - t1.position0 );
            float d1 = glm::dot( -normalT1, t1.position0 );
            std::array<float, 3> distancesT0 = {
                    computePlaneDistance( normalT1, t0.position0, d1 ),
                    computePlaneDistance( normalT1, t0.position1, d1 ),
                    computePlaneDistance( normalT1, t0.position2, d1 )
            };

            if ( distancesT0[0] > 0 && distancesT0[1] > 0 && distancesT0[2] > 0 ||
                 distancesT0[0] < 0 && distancesT0[1] < 0 && distancesT0[2] < 0 )
                return false;

            glm::vec3 normalT0 = glm::cross( t0.position1 - t0.position0,
                                             t0.position2 - t0.position0 );
            float d0 = glm::dot( -normalT0, t0.position0 );
            std::array<float, 3> distancesT1 = {
                    computePlaneDistance( normalT0, t1.position0, d0 ),
                    computePlaneDistance( normalT0, t1.position1, d0 ),
                    computePlaneDistance( normalT0, t1.position2, d0 )
            };
            if ( distancesT1[0] > 0 && distancesT1[1] > 0 && distancesT1[2] > 0 ||
                 distancesT1[0] < 0 && distancesT1[1] < 0 && distancesT1[2] < 0 )
                return false;

            glm::vec3 intersectionDirection = glm::cross( normalT0, normalT1 );

            // finding the triangle point which is on the other side of the plane
            std::array<float, 2> interval0 = computeTriangleLineInterval( t0,
                                                                          intersectionDirection,
                                                                          distancesT0 );
            std::array<float, 2> interval1 = computeTriangleLineInterval( t1,
                                                                          intersectionDirection,
                                                                          distancesT1 );

            return util::doIntervalsIntersect( interval0, interval1 );
        }

        bool isInsideBox( const Triangle &triangle, const glm::vec3 &minAABB,
                          const glm::vec3 &maxAABB )
        {
            // Lambda to check if a point is inside the AABB
            auto isPointInside = [&]( const glm::vec3 &point ) -> bool {
                return ( point.x >= minAABB.x && point.x <= maxAABB.x ) &&
                       ( point.y >= minAABB.y && point.y <= maxAABB.y ) &&
                       ( point.z >= minAABB.z && point.z <= maxAABB.z );
            };

            // Check if all vertices of the triangle are inside the AABB
            return isPointInside( triangle.position0 ) &&
                   isPointInside( triangle.position1 ) &&
                   isPointInside( triangle.position2 );
        }

        float computePlaneDistance( const glm::vec3 &normal, const glm::vec3 &point,
                                    float distance )
        {
            return glm::dot( normal, point ) + distance;
        }

        std::array<float, 2> computeTriangleLineInterval( const Triangle &triangle,
                                                          const glm::vec3 &intersectionDirection,
                                                          const std::array<float, 3> &distances )
        {
            float p0 = projectOntoAxis( intersectionDirection, triangle.position0 );
            float p1 = projectOntoAxis( intersectionDirection, triangle.position1 );
            float p2 = projectOntoAxis( intersectionDirection, triangle.position2 );

            std::array<float, 2> interval = {};
            if ( util::differentSign( distances[0], distances[1], distances[2] ))
            {
                interval[0] =
                        p1 +
                        ( p0 - p1 ) * ( distances[1] / ( distances[1] - distances[0] ));
                interval[1] =
                        p2 +
                        ( p0 - p2 ) * ( distances[2] / ( distances[2] - distances[0] ));
            } else if ( util::differentSign( distances[1], distances[0], distances[2] ))
            {
                interval[0] =
                        p0 +
                        ( p1 - p0 ) * ( distances[0] / ( distances[0] - distances[1] ));
                interval[1] =
                        p2 +
                        ( p1 - p2 ) * ( distances[2] / ( distances[2] - distances[1] ));
            } else
            {
                interval[0] =
                        p0 +
                        ( p2 - p0 ) * ( distances[0] / ( distances[0] - distances[2] ));
                interval[1] =
                        p1 +
                        ( p2 - p1 ) * ( distances[1] / ( distances[1] - distances[2] ));
            }

            return interval;
        }

        float projectOntoAxis( const glm::vec3 &distance, const glm::vec3 &trianglePoint )
        {
            float maxDistance = std::max(
                    { abs( distance.x ), abs( distance.y ), abs( distance.z ) } );
            if ( abs( distance.x ) == maxDistance ) return trianglePoint.x;
            else if ( abs( distance.y ) == maxDistance )return trianglePoint.y;
            return trianglePoint.z;
        }

        glm::vec3 calculateCentroid(
                const std::vector<std::shared_ptr<TriangleFace>> &triangleFaces )
        {
            // calculate centroid of mesh based on the triangle-representation of the model
            glm::vec3 centroid = { 0, 0, 0 };
            for ( const auto &triangleFace: triangleFaces )
            {
                glm::vec3 triangleCenter = triangleFace->getCenter();
                centroid.x += triangleCenter.x / static_cast<float>(triangleFaces.size());
                centroid.y += triangleCenter.y / static_cast<float>(triangleFaces.size());
                centroid.z += triangleCenter.z / static_cast<float>(triangleFaces.size());
            }
            return centroid;
        }
    }

    namespace octree
    {
        void findleavesAtMaxDepth( OctreeNode* node, int depth, int &maxDepth,
                                   std::vector<OctreeNode*> &leaves )
        {
            if ( node->isLeaf )
            {
                if ( depth > maxDepth )
                {
                    maxDepth = depth;
                    leaves.clear();
                }
                if ( depth == maxDepth )
                {
                    leaves.push_back( node );
                }
            } else
            {
                for ( OctreeNode* child: node->children )
                {
                    findleavesAtMaxDepth( child, depth + 1, maxDepth, leaves );
                }
            }
        }

        std::vector<Voxel> toVoxel( OctreeNode* node, int depth )
        {
            std::vector<Voxel> result;
            std::vector<OctreeNode*> leaves;
            int maxDepth = -1;

            util::octree::findleavesAtMaxDepth( node, depth, maxDepth, leaves );
            int counter = 0;
            for ( const OctreeNode* leaf: leaves )
            {
                if ( !leaf->isAir )
                {
                    Voxel v = util::voxel::createVoxel( leaf->position,
                                                        result.size() * 24,
                                                        leaf->edgeLength );
                    result.push_back( v );
                    counter++;
                }
            }
            return result;
        }
    }//namespace octree
    namespace voxel
    {
        Voxel
        createVoxel( const glm::vec3 &position, unsigned int offset, float edgeLength )
        {
            float halfLength = edgeLength / 2.0f;

            glm::vec3 normals[6] = {
                    { 0,  0,  1 },  // Front
                    { 0,  0,  -1 },  // Back
                    { 0,  1,  0 },  // Top
                    { 0,  -1, 0 },  // Bottom
                    { -1, 0,  0 },  // Left
                    { 1,  0,  0 }   // Right
            };

            Vertex frontVertices[4] = {
                    { position.x - halfLength, position.y - halfLength,
                                                                        position.z +
                                                                        halfLength,
                            normals[0].x, normals[0].y, normals[0].z },
                    { position.x + halfLength, position.y - halfLength, position.z +
                                                                        halfLength,
                            normals[0].x, normals[0].y, normals[0].z },
                    { position.x - halfLength, position.y + halfLength, position.z +
                                                                        halfLength,
                            normals[0].x, normals[0].y, normals[0].z },
                    { position.x + halfLength, position.y + halfLength, position.z +
                                                                        halfLength,
                            normals[0].x, normals[0].y, normals[0].z }
            };

            Vertex backVertices[4] = {
                    { position.x + halfLength, position.y - halfLength,
                                                                        position.z -
                                                                        halfLength,
                            normals[1].x, normals[1].y, normals[1].z },
                    { position.x - halfLength, position.y - halfLength, position.z -
                                                                        halfLength,
                            normals[1].x, normals[1].y, normals[1].z },
                    { position.x + halfLength, position.y + halfLength, position.z -
                                                                        halfLength,
                            normals[1].x, normals[1].y, normals[1].z },
                    { position.x - halfLength, position.y + halfLength, position.z -
                                                                        halfLength,
                            normals[1].x, normals[1].y, normals[1].z }
            };


            Vertex topVertices[4] = {
                    { position.x - halfLength, position.y + halfLength,
                                                                        position.z +
                                                                        halfLength,
                            normals[2].x, normals[2].y, normals[2].z },
                    { position.x + halfLength, position.y + halfLength, position.z +
                                                                        halfLength,
                            normals[2].x, normals[2].y, normals[2].z },
                    { position.x - halfLength, position.y + halfLength, position.z -
                                                                        halfLength,
                            normals[2].x, normals[2].y, normals[2].z },
                    { position.x + halfLength, position.y + halfLength, position.z -
                                                                        halfLength,
                            normals[2].x, normals[2].y, normals[2].z }
            };

            Vertex bottomVertices[4] = {
                    { position.x - halfLength, position.y - halfLength,
                                                                        position.z -
                                                                        halfLength,
                            normals[3].x, normals[3].y, normals[3].z },
                    { position.x + halfLength, position.y - halfLength, position.z -
                                                                        halfLength,
                            normals[3].x, normals[3].y, normals[3].z },
                    { position.x - halfLength, position.y - halfLength, position.z +
                                                                        halfLength,
                            normals[3].x, normals[3].y, normals[3].z },
                    { position.x + halfLength, position.y - halfLength, position.z +
                                                                        halfLength,
                            normals[3].x, normals[3].y, normals[3].z }
            };

            Vertex leftVertices[4] = {
                    { position.x - halfLength, position.y - halfLength,
                                                                        position.z -
                                                                        halfLength,
                            normals[4].x, normals[4].y, normals[4].z },
                    { position.x - halfLength, position.y - halfLength, position.z +
                                                                        halfLength,
                            normals[4].x, normals[4].y, normals[4].z },
                    { position.x - halfLength, position.y + halfLength, position.z -
                                                                        halfLength,
                            normals[4].x, normals[4].y, normals[4].z },
                    { position.x - halfLength, position.y + halfLength, position.z +
                                                                        halfLength,
                            normals[4].x, normals[4].y, normals[4].z }
            };


            Vertex rightVertices[4] = {
                    { position.x + halfLength, position.y - halfLength,
                                                                        position.z +
                                                                        halfLength,
                            normals[5].x, normals[5].y, normals[5].z },
                    { position.x + halfLength, position.y - halfLength, position.z -
                                                                        halfLength,
                            normals[5].x, normals[5].y, normals[5].z },
                    { position.x + halfLength, position.y + halfLength, position.z +
                                                                        halfLength,
                            normals[5].x, normals[5].y, normals[5].z },
                    { position.x + halfLength, position.y + halfLength, position.z -
                                                                        halfLength,
                            normals[5].x, normals[5].y, normals[5].z }
            };

            // Create voxel faces with calculated m_vertices and the provided offset
            VoxelFace frontFace( frontVertices, offset + 0 );
            VoxelFace backFace( backVertices, offset + 4 );
            VoxelFace topFace( topVertices, offset + 8 );
            VoxelFace bottomFace( bottomVertices, offset + 12 );
            VoxelFace leftFace( leftVertices, offset + 16 );
            VoxelFace rightFace( rightVertices, offset + 20 );

            // Create and return the voxel
            return { frontFace, backFace, topFace, bottomFace, leftFace, rightFace };
        }
    }//namespace voxel
    namespace bvh
    {
        void createChildren( BVHNode* node, int depth, int maxDepth )
        {
            if ( depth >= maxDepth || node->triangleFaces.size() <= 1 )
                return;

            // initialization of child nodes
            node->left = new BVHNode( node );
            node->right = new BVHNode( node );


            // Find the longest axis (x, y, or z)
            glm::vec3 bboxSize = node->highest - node->lowest;
            int longestAxis = 0;
            if ( bboxSize.y > bboxSize.x ) longestAxis = 1;
            if ( bboxSize.z > bboxSize.y && bboxSize.z > bboxSize.x ) longestAxis = 2;

            // Compute the center of the bounding volume along the longest axis
            float center = ( node->highest[longestAxis] + node->lowest[longestAxis] ) / 2;

            // Map triangles to one of two bounding volumes based on the center
            for ( const std::shared_ptr<TriangleFace> &t: node->triangleFaces )
            {
                if ( t->getCenter()[longestAxis] < center )
                    node->left->triangleFaces.push_back( t );
                else
                    node->right->triangleFaces.push_back( t );
            }

            if ( node->left->triangleFaces.empty() || node->right->triangleFaces.empty())
            {
                delete node->left;
                delete node->right;
                node->left = nullptr;
                node->right = nullptr;
                return;
            }

            // define min/max vectors for child nodes
            node->left->highest = util::geometry::maxVec(
                    util::geometry::extractPositions( node->left->triangleFaces ));
            node->left->lowest = util::geometry::minVec(
                    util::geometry::extractPositions( node->left->triangleFaces ));
            node->right->highest = util::geometry::maxVec(
                    util::geometry::extractPositions( node->right->triangleFaces ));
            node->right->lowest = util::geometry::minVec(
                    util::geometry::extractPositions( node->right->triangleFaces ));

            createChildren( node->left, depth + 1, maxDepth );
            createChildren( node->right, depth + 1, maxDepth );

        }

        void getLeaves( BVHNode* node, std::vector<BVHNode*> &leaves )
        {
            if ( node->left == nullptr && node->right == nullptr )
            {
                leaves.push_back( node );
            } else
            {
                getLeaves( node->left, leaves );
                getLeaves( node->right, leaves );
            }
        }
    }//namespace bvh


}