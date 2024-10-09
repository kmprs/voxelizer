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
    auto octree = new OctreeNode { nullptr, 2, WORLD_CENTER };
    m_voxelizer.buildOctree( octree, 0, 2);

    // TODO: convert the octree to voxels
//    m_voxels.insert( m_voxels.end(), voxels.begin(), voxels.end());

    delete octree;
}

