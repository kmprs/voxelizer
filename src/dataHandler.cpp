#include "dataHandler.hpp"

#include <utility>

DataHandler::DataHandler( std::string path, FileFormat format ) :
        m_path(std::move( path ))
{
    if (format == OBJ) m_reader = std::make_unique<OBJParser>();
    m_triangleFaces = m_reader->parse( m_path );
    voxelize();
}

std::vector<std::shared_ptr<Voxel>> DataHandler::getVoxels() const
{
    return {};
}

std::vector<std::shared_ptr<TriangleFace>> DataHandler::getTriangleFaces() const
{
    return m_triangleFaces;
}

void DataHandler::voxelize()
{

}

