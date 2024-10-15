#include "dataHandler.hpp"

#include <utility>

DataHandler::DataHandler( std::string path, FileFormat format ) :
        m_path( std::move( path ))
{
    if ( format == OBJ ) m_reader = std::make_unique<OBJParser>();
    m_triangleFaces = m_reader->parse( m_path );
    m_voxelizer = { m_triangleFaces };
    voxelize();
}

std::vector<std::shared_ptr<Voxel>> DataHandler::getVoxels() const
{
    return m_voxels;
}

std::vector<std::shared_ptr<TriangleFace>> DataHandler::getTriangleFaces() const
{
    return m_triangleFaces;
}

void DataHandler::voxelize()
{
    // build bvh from triangleFaces
    auto octree = new OctreeNode { nullptr, 2, WORLD_CENTER };
    auto bvh = new BVHNode{ nullptr };

    bvh->triangleFaces = m_triangleFaces;
    util::bvh::createChildren( bvh, 0, BVH_DEPTH);
    std::vector<BVHNode*> leaves;
    bvh->getLeaves( leaves );
    std::cout << leaves.size() << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    int counter = 0;
    m_voxelizer.buildOctree( octree, 0, RESOLUTION_LEVEL, leaves, counter );

    auto stop = std::chrono::high_resolution_clock::now();
    auto durationS = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    auto durationMS = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Build Octree: " << durationS.count() << "s:" << durationMS.count()%1000 << "ms" << std::endl;
    std::cout << "Triangle Intersection Test Counter: " << counter << std::endl;

    std::vector<Voxel> voxels = util::octree::toVoxel(octree, 0);
    for ( const Voxel& v : voxels )
    {
        m_voxels.push_back(std::make_shared<Voxel>(v));
    }

    delete bvh;
    delete octree;
}

