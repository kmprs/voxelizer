#include "octreeVoxelizer.hpp"


std::vector<Voxel> OctreeVoxelizer::run(
        const std::vector<std::shared_ptr<TriangleFace>> triangleFaces )
{
    for ( const std::shared_ptr<TriangleFace> &t: triangleFaces )
    {
        m_meshTriangles.push_back( t );
    }

    auto octree = new OctreeNode { nullptr, 2, WORLD_CENTER };
    auto bvh = new BVHNode{ nullptr };

    bvh->triangleFaces = m_meshTriangles;
    util::bvh::createChildren( bvh, 0, BVH_DEPTH);
    std::vector<BVHNode*> leaves;
    bvh->getLeaves( leaves );
    // DEBUG
    long counter = 0;
    buildOctree( octree, 0, RESOLUTION_LEVEL, leaves, counter );
    std::cout << "Triangle Intersection Test Counter: " << counter << std::endl;

    std::vector<Voxel> voxels = util::octree::toVoxel(octree, 0);
    for ( const Voxel& v : voxels )
    {
        voxels.push_back(v);
    }

    delete bvh;
    delete octree;

    return voxels;
}


void OctreeVoxelizer::buildOctree( OctreeNode* node, int depth, int maxDepth,
                                   std::vector<BVHNode*> &leaves, long &counter )
{
    if ( depth >= maxDepth ) return;
    // fetch vertex positions from octree node
    std::array<Triangle, 12> voxelTriangles = util::geometry::getCubeTriangles(
            node->position,
            node->edgeLength );

    std::vector<glm::vec3> vertexPositions;
    vertexPositions.reserve(36);

    for ( const Triangle &t: voxelTriangles )
    {
        vertexPositions.push_back( t.position0 );
        vertexPositions.push_back( t.position1 );
        vertexPositions.push_back( t.position2 );
    }

    // calculate extremes of voxels
    glm::vec3 maxVec = util::geometry::maxVec( vertexPositions );
    glm::vec3 minVec = util::geometry::minVec( vertexPositions );


    for ( auto bvhNode: leaves )
    {
        if ( !util::geometry::doBoundingVolumesIntersect( minVec, maxVec,
                                                          bvhNode->lowest,
                                                          bvhNode->highest ))
        {
            continue;
        }


        for ( const Triangle &voxelTriangle: voxelTriangles )
        {
            for ( const std::shared_ptr<TriangleFace> &meshTriangleFace: bvhNode->triangleFaces )
            {
                Triangle meshTriangle = meshTriangleFace->toTriangle();
                counter++;
                if ( doTrianglesIntersect( meshTriangle, voxelTriangle ))
                {
                    node->isAir = false;
                    if ( depth < maxDepth - 1 )
                    {
                        node->createChildren();
                        for ( OctreeNode* child: node->children )
                        {
                            buildOctree( child, depth + 1, maxDepth, leaves, counter );
                        }
                    }
                    return;
                }
            }
        }
    }
}


bool OctreeVoxelizer::doTrianglesIntersect( const Triangle &t0, const Triangle &t1 )
{
    // this method is based on the algorithm presented by Thomas Moeller
    // test if triangles are on the same side of the plane build by the other triangle
    // if yes, both triangles do not intersect

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

float OctreeVoxelizer::computePlaneDistance( const glm::vec3 &normal, const glm::vec3 &point,
                                             float distance )
{
    return glm::dot( normal, point ) + distance;
}

std::array<float, 2>
OctreeVoxelizer::computeTriangleLineInterval( const Triangle &triangle,
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
                p1 + ( p0 - p1 ) * ( distances[1] / ( distances[1] - distances[0] ));
        interval[1] =
                p2 + ( p0 - p2 ) * ( distances[2] / ( distances[2] - distances[0] ));
    } else if ( util::differentSign( distances[1], distances[0], distances[2] ))
    {
        interval[0] =
                p0 + ( p1 - p0 ) * ( distances[0] / ( distances[0] - distances[1] ));
        interval[1] =
                p2 + ( p1 - p2 ) * ( distances[2] / ( distances[2] - distances[1] ));
    } else
    {
        interval[0] =
                p0 + ( p2 - p0 ) * ( distances[0] / ( distances[0] - distances[2] ));
        interval[1] =
                p1 + ( p2 - p1 ) * ( distances[1] / ( distances[1] - distances[2] ));
    }

    return interval;
}

float
OctreeVoxelizer::projectOntoAxis( const glm::vec3 &distance, const glm::vec3 &trianglePoint )
{
    float maxDistance = std::max(
            { abs( distance.x ), abs( distance.y ), abs( distance.z ) } );
    if ( abs( distance.x ) == maxDistance ) return trianglePoint.x;
    else if ( abs( distance.y ) == maxDistance )return trianglePoint.y;
    return trianglePoint.z;
}
