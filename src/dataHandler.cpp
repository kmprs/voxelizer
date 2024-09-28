#include "dataHandler.hpp"

#include <utility>

DataHandler::DataHandler( std::string path, FileFormat format ) :
        m_path(std::move( path ))
{
    if (format == OBJ) m_reader = std::make_unique<OBJReader>();
    m_triangleFaces = m_reader->read(m_path);

}

std::vector<std::shared_ptr<Voxel>> DataHandler::getVoxels() const
{
    return {};
}

std::vector<std::shared_ptr<TriangleFace>> DataHandler::getTriangleFaces() const
{
    return {};
}
