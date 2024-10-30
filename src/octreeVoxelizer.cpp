#include "octreeVoxelizer.hpp"


extern std::shared_ptr<DataHandler> dataHandler;


std::vector<Voxel> OctreeVoxelizer::run(
        const std::vector<std::shared_ptr<TriangleFace>> &triangleFaces, int resolution
        )
{
    auto octree = new OctreeNode{ nullptr, 2, dataHandler->getWorldCenter() };
    auto bvh = new BVHNode{ nullptr };

    bvh->triangleFaces = triangleFaces;
    util::bvh::createChildren( bvh, 0, BVH_DEPTH );
    std::vector<BVHNode*> bvhLeaves;
    bvh->getLeaves( bvhLeaves );
    // DEBUG
    long counter = 0;
    buildOctree( octree, 0, resolution, bvhLeaves, counter );
    std::cout << "\nNumber of leaves in bvh node: " << bvhLeaves.size() << std::endl;
    std::cout << "Triangle Intersection Test Counter: " << counter << std::endl;

    std::vector<Voxel> voxels = util::octree::toVoxel( octree, 0 );

    delete bvh;
    delete octree;

    return voxels;
}


void OctreeVoxelizer::buildOctree( OctreeNode* octreeNode, int depth, int maxDepth,
                                   std::vector<BVHNode*> &leaves, long &counter )
{
    // fetch vertex positions from octree octreeNode
    std::array<Triangle, 12> voxelTriangles = util::geometry::getCubeTriangles(
            octreeNode->position,
            octreeNode->edgeLength );

    std::vector<glm::vec3> voxelPositions;
    for ( const Triangle &triangle: voxelTriangles )
    {
        voxelPositions.push_back( triangle.position0 );
        voxelPositions.push_back( triangle.position1 );
        voxelPositions.push_back( triangle.position2 );
    }
    glm::vec3 minVoxel = util::geometry::minVec( voxelPositions );
    glm::vec3 maxVoxel = util::geometry::maxVec( voxelPositions );


    for ( auto bvhNode: leaves )
    {
        if ( bvhNode->triangleFaces.empty()) continue;
        if ( !util::geometry::doBoundingVolumesIntersect( minVoxel, maxVoxel,
                                                          bvhNode->lowest,
                                                          bvhNode->highest ))
            continue;
        for ( const Triangle &voxelTriangle: voxelTriangles )
        {
            for ( const std::shared_ptr<TriangleFace> &meshTriangleFace: bvhNode->triangleFaces )
            {
                Triangle meshTriangle = meshTriangleFace->toTriangle();
                counter++;
                if ( util::geometry::doTrianglesIntersect( meshTriangle, voxelTriangle )
                     || util::geometry::isInsideBox( meshTriangle, minVoxel, maxVoxel ))
                {
                    octreeNode->isAir = false;
                    if ( depth < maxDepth - 1 )
                    {
                        octreeNode->createChildren();
                        for ( OctreeNode* child: octreeNode->children )
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



