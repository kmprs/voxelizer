#include "bvhVoxelizer.hpp"


extern std::shared_ptr<DataHandler> dataHandler;


std::vector<Voxel>
BVHVoxelizer::run( const vecTriangleFaceSharedPtr &triangleFaces,
                   int resolution )
{
    // setting up the BVH
    auto bvh = new BVHNode{ nullptr };
    bvh->triangleFaces = triangleFaces;
    util::bvh::createChildren( bvh, 0, BVH_DEPTH );
    std::vector<BVHNode*> leaves;
    bvh->getLeaves( leaves );

    std::vector<Voxel> result;
    // voxel size is adjusted to the Octree/OptimizedVoxelizer for better comparison
    float voxelSize = 1.f / std::pow( 2, resolution - 2 );
    int numVoxelsPerDimension = static_cast<int>(std::ceil(
            2.f / voxelSize ));

    for ( int i = 0; i < numVoxelsPerDimension; ++i )
    {
        for ( int j = 0; j < numVoxelsPerDimension; ++j )
        {
            for ( int k = 0; k < numVoxelsPerDimension; ++k )
            {
                bool isSolid = false;
                float x = -1.0f + ( static_cast<float>(i) + 0.5f ) * voxelSize;
                float y = -1.0f + ( static_cast<float>(j) + 0.5f ) * voxelSize;
                float z = -1.0f + ( static_cast<float>(k) + 0.5f ) * voxelSize;

                std::array<Triangle, 12> voxelTriangles = util::geometry::getCubeTriangles(
                        { x, y, z }, voxelSize );
                // calculate voxel AABB
                std::vector<glm::vec3> edgeCoordinates;
                for ( const Triangle &triangle: voxelTriangles )
                {
                    edgeCoordinates.push_back( triangle.position0 );
                    edgeCoordinates.push_back( triangle.position1 );
                    edgeCoordinates.push_back( triangle.position2 );
                }
                glm::vec3 minVoxel = util::geometry::minVec( edgeCoordinates );
                glm::vec3 maxVoxel = util::geometry::maxVec( edgeCoordinates );

                for ( const auto bvhNode: leaves )
                {
                    if ( bvhNode->triangleFaces.empty()) continue;
                    if ( !util::geometry::doBoundingVolumesIntersect( minVoxel, maxVoxel,
                                                                      bvhNode->lowest,
                                                                      bvhNode->highest ))
                        continue;

                    for ( const auto &meshTriangleFaces: bvhNode->triangleFaces )
                    {
                        for ( const auto &voxelTriangle: voxelTriangles )
                        {
                            if ( util::geometry::doTrianglesIntersect( voxelTriangle,
                                                                       meshTriangleFaces->toTriangle()))
                            {
                                isSolid = true;
                                break;
                            }
                        }
                        if ( isSolid ) break;
                    }
                    if ( isSolid ) break;
                }
                if ( isSolid )
                {
                    result.push_back( util::voxel::createVoxel( { x, y, z },
                                                                result.size() *
                                                                VOXEL_MEMORY_SIZE,
                                                                voxelSize ));
                }
            }
        }
    }

    delete bvh;
    return result;
}
