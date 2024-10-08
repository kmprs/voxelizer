#include "dataHandler.hpp"

#include <utility>

DataHandler::DataHandler( std::string path, FileFormat format ) :
        m_path( std::move( path ))
{
    if ( format == OBJ ) m_reader = std::make_unique<OBJParser>();
    m_triangleFaces = m_reader->parse( m_path );
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
    std::vector<std::shared_ptr<Voxel>> voxels = m_voxelizer.convert( m_triangleFaces );
    m_voxels.insert( m_voxels.end(), voxels.begin(), voxels.end() );
}

