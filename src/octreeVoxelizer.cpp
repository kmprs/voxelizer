#include "octreeVoxelizer.hpp"


extern std::shared_ptr<DataHandler> dataHandler;


std::vector<Voxel>
OctreeVoxelizer::run( const vecTriangleFace &triangleFaces,
                      int resolution )
{
    auto octree = new OctreeNode{ nullptr, 2, dataHandler->getWorldCenter() };

    buildOctree( octree, 0, resolution, triangleFaces );
    std::vector<Voxel> voxels = util::octree::toVoxel( octree, 0 );

    delete octree;
    return voxels;
}


void OctreeVoxelizer::buildOctree(
        OctreeNode* octreeNode, int depth, int maxDepth,
        const vecTriangleFace &triangleFaces )
{
    // fetch vertex positions from octree octreeNode
    std::array<Triangle, 12> voxelTriangles = util::geometry::getCubeTriangles(
            octreeNode->position,
            octreeNode->edgeLength );

    std::vector<glm::vec3> edgeCoordinates;
    for ( const Triangle &triangle: voxelTriangles )
    {
        edgeCoordinates.push_back( triangle.position0 );
        edgeCoordinates.push_back( triangle.position1 );
        edgeCoordinates.push_back( triangle.position2 );
    }
    glm::vec3 minVoxel = util::geometry::minVec( edgeCoordinates );
    glm::vec3 maxVoxel = util::geometry::maxVec( edgeCoordinates );


    for ( const Triangle &voxelTriangle: voxelTriangles )
    {
        for ( const std::shared_ptr<TriangleFace> &meshTriangleFace: triangleFaces )
        {
            Triangle meshTriangle = meshTriangleFace->toTriangle();
            if ( util::geometry::doTrianglesIntersect( meshTriangle, voxelTriangle )
                 || util::geometry::isInsideBox( meshTriangle, minVoxel, maxVoxel ))
            {
                octreeNode->isAir = false;
                if ( depth < maxDepth - 1 )
                {
                    octreeNode->createChildren();
                    for ( OctreeNode* child: octreeNode->children )
                    {
                        buildOctree( child, depth + 1, maxDepth, triangleFaces );
                    }
                }
                return;
            }
        }
    }
}